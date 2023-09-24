#include "cmddef.h"
#include "parser.h"
#include "array.h"
#include "token.h"

static void	lexer_redirection_type_get(t_token *token, t_file *file)
{
	if (token_is(token, TOKEN_IN))
		file->type = FILE_IN;
	else if (token_is(token, TOKEN_OUT))
		file->type = FILE_OUT;
	else if (token_is(token, TOKEN_HEREDOC))
		file->type = FILE_HEREDOC;
	else if (token_is(token, TOKEN_APPEND))
		file->type = FILE_APPEND;
}

int	parser_redir_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_token	*redir;
	t_token	*value;
	t_file	file;

	redir = (t_token *) arr_get(tokens, (*index)++);
	value = (t_token *) arr_get(tokens, (*index)++);
	lexer_redirection_type_get(redir, &file);
	if (file.type == FILE_HEREDOC)
		// TODO: add heredoc logic
		file.data.id = 0;
	else
	{
		if (parser_vars_copy(value, arr_size(&command->files), &command->vars_files))
			return (1);
		file.data.path = value->str;
	}
	return (arr_add(&command->files, &file));
}