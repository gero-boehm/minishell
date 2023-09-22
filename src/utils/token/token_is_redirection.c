#include "tokendef.h"
#include "str.h"

int	token_is_redir_in(t_token *token)
{
	return (str_eq(token->str, "<"));
}

int	token_is_redir_out(t_token *token)
{
	return (str_eq(token->str, ">"));
}

int	token_is_redir_heredoc(t_token *token)
{
	return (str_eq(token->str, "<<"));
}

int	token_is_redir_out_append(t_token *token)
{
	return (str_eq(token->str, ">>"));
}

int token_is_possibly_redir(t_token *token)
{
	char c;

	c = *token->str;
	return (c == '<' || c == '>');
}
