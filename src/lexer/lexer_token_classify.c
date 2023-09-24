#include "tokendef.h"
#include "array.h"
#include "str.h"
#include "error.h"

static int lexer_token_is_operand(t_token *token)
{
	return (str_char_in_set("&|", *token->str));
}

static int lexer_token_is_redirection(t_token *token)
{
	return (str_char_in_set("<>", *token->str));
}

static int lexer_token_is_parenthesis(t_token *token)
{
	return (str_char_in_set("()", *token->str));
}

static int lexer_token_classify_operator_and(t_token *token)
{
	if (!str_eq(token->str, "&&"))
		return (0);
	token->type |= TOKEN_AND;
	return (1);
}

static int lexer_token_classify_operator_or(t_token *token)
{
	if (!str_eq(token->str, "||"))
		return (0);
	token->type |= TOKEN_OR;
	return (1);
}

static int lexer_token_classify_operator_pipe(t_token *token)
{
	if (!str_eq(token->str, "|"))
		return (0);
	token->type |= TOKEN_PIPE;
	return (1);
}

static int lexer_token_classify_redirection_in(t_token *token)
{
	if (!str_eq(token->str, "<"))
		return (0);
	token->type |= TOKEN_IN;
	return (1);
}

static int lexer_token_classify_redirection_out(t_token *token)
{
	if (!str_eq(token->str, ">"))
		return (0);
	token->type |= TOKEN_OUT;
	return (1);
}

static int lexer_token_classify_redirection_heredoc(t_token *token)
{
	if (!str_eq(token->str, "<<"))
		return (0);
	token->type |= TOKEN_HEREDOC;
	return (1);
}

static int lexer_token_classify_redirection_append(t_token *token)
{
	if (!str_eq(token->str, ">>"))
		return (0);
	token->type |= TOKEN_APPEND;
	return (1);
}

static int lexer_token_classify_parenthesis_opening(t_token *token)
{
	if (!str_eq(token->str, "("))
		return (0);
	token->type |= TOKEN_OPENING;
	return (1);
}

static int lexer_token_classify_parenthesis_closing(t_token *token)
{
	if (!str_eq(token->str, ")"))
		return (0);
	token->type |= TOKEN_CLOSING;
	return (1);
}

static void lexer_token_classify_operator(t_token *token)
{
	token->type |= TOKEN_OPERATOR;
	if (lexer_token_classify_operator_and(token))
		return ;
	if (lexer_token_classify_operator_or(token))
		return ;
	if (lexer_token_classify_operator_pipe(token))
		return ;
	token->type = TOKEN_INVALID;
}

static void lexer_token_classify_redirection(t_token *token)
{
	token->type |= TOKEN_REDIRECTION;
	if (lexer_token_classify_redirection_in(token))
		return ;
	if (lexer_token_classify_redirection_out(token))
		return ;
	if (lexer_token_classify_redirection_heredoc(token))
		return ;
	if (lexer_token_classify_redirection_append(token))
		return ;
	token->type = TOKEN_INVALID;
}

static void lexer_token_classify_parentheses(t_token *token)
{
	token->type |= TOKEN_PARENTHESIS;
	if (lexer_token_classify_parenthesis_opening(token))
		return ;
	if (lexer_token_classify_parenthesis_closing(token))
		return ;
	token->type = TOKEN_INVALID;
}

static void lexer_token_classify_string(t_token *token)
{
	token->type |= TOKEN_STRING;
}

void	lexer_tokens_classify(t_array *tokens)
{
	unsigned long	i;
	t_token			*token;

	i = 0;
	while (i < arr_size(tokens))
	{
		token = (t_token *) arr_get(tokens, i);
		token->type = TOKEN_INVALID;
		if (lexer_token_is_operand(token))
			lexer_token_classify_operator(token);
		else if (lexer_token_is_redirection(token))
			lexer_token_classify_redirection(token);
		else if (lexer_token_is_parenthesis(token))
			lexer_token_classify_parentheses(token);
		else
			lexer_token_classify_string(token);
		i++;
	}
}
