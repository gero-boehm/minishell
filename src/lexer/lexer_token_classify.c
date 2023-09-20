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

static int lexer_token_classify_operand_and(t_token *token)
{
	if (!str_eq(token->str, "&&"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_AND;
	return (1);
}

static int lexer_token_classify_operand_or(t_token *token)
{
	if (!str_eq(token->str, "||"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_OR;
	return (1);
}

static int lexer_token_classify_operand_pipe(t_token *token)
{
	if (!str_eq(token->str, "|"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_PIPE;
	return (1);
}

static int lexer_token_classify_redirection_in(t_token *token)
{
	if (!str_eq(token->str, "<"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_IN;
	return (1);
}

static int lexer_token_classify_redirection_heredoc(t_token *token)
{
	if (!str_eq(token->str, "<<"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_HEREDOC;
	return (1);
}

static int lexer_token_classify_redirection_out(t_token *token)
{
	if (!str_eq(token->str, ">"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_OUT;
	return (1);
}

static int lexer_token_classify_redirection_out_append(t_token *token)
{
	if (!str_eq(token->str, ">>"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_OUT_APPEND;
	return (1);
}

static int lexer_token_classify_parenthesis_opening(t_token *token)
{
	if (!str_eq(token->str, "("))
		return (0);
	token->subtype = TOKEN_SUBTYPE_OPENING;
	return (1);
}

static int lexer_token_classify_parenthesis_closing(t_token *token)
{
	if (!str_eq(token->str, ")"))
		return (0);
	token->subtype = TOKEN_SUBTYPE_CLOSING;
	return (1);
}

static void lexer_token_classify_operand(t_token *token)
{
	token->type = TOKEN_TYPE_OPERAND;
	if (lexer_token_classify_operand_and(token))
		return ;
	if (lexer_token_classify_operand_or(token))
		return ;
	if (lexer_token_classify_operand_pipe(token))
		return ;
	error_syntax(token->str);
}

static void lexer_token_classify_redirection(t_token *token)
{
	token->type = TOKEN_TYPE_REDIRECTION;
	if (lexer_token_classify_redirection_in(token))
		return ;
	if (lexer_token_classify_redirection_heredoc(token))
		return ;
	if (lexer_token_classify_redirection_out(token))
		return ;
	if (lexer_token_classify_redirection_out_append(token))
		return ;
	error_syntax(token->str);
}

static void lexer_token_classify_parentheses(t_token *token)
{
	token->type = TOKEN_TYPE_PARENTHESIS;
	if (lexer_token_classify_parenthesis_opening(token))
		return ;
	if (lexer_token_classify_parenthesis_closing(token))
		return ;
	error_syntax(token->str);
}

static void lexer_token_classify_string(t_token *token)
{
	token->type = TOKEN_TYPE_STRING;
	token->subtype = TOKEN_SUBTYPE_NONE;
}

void	lexer_tokens_classify(t_array *tokens)
{
	unsigned long	i;
	t_token			*token;

	i = 0;
	while (i < arr_size(tokens))
	{
		token = (t_token *) arr_get(tokens, i);
		if (lexer_token_is_operand(token))
			lexer_token_classify_operand(token);
		else if (lexer_token_is_redirection(token))
			lexer_token_classify_redirection(token);
		else if (lexer_token_is_parenthesis(token))
			lexer_token_classify_parentheses(token);
		else
			lexer_token_classify_string(token);
		i++;
	}
}