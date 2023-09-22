#include "cmddef.h"
#include "token.h"

static void	set_file_type(t_file *file, t_file_type type)
{
	file->type = type;
}

int	token_redirection_type_get(t_token *token, t_file *file)
{
	if (token_is_redir_in(token))
		return (set_file_type(file, FILE_IN), 0);
	if (token_is_redir_out(token))
		return (set_file_type(file, FILE_OUT), 0);
	if (token_is_redir_heredoc(token))
		return (set_file_type(file, FILE_IN_HEREDOC), 0);
	if (token_is_redir_out_append(token))
		return (set_file_type(file, FILE_OUT_APPEND), 0);
	return (1);
}