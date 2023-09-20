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

int token_is_redir(t_token *token)
{
	return (
		token_is_redir_in(token) ||
		token_is_redir_out(token) ||
		token_is_redir_heredoc(token) ||
		token_is_redir_out_append(token)
	);
}
