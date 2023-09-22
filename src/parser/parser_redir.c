#include "cmddef.h"
#include "array.h"
#include "token.h"
#include "error.h"
#include "parser.h"

int	parser_redir_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_token	*redir;
	t_token	*value;
	t_file	file;

	redir = (t_token *) arr_get(tokens, (*index)++);
	if (token_redirection_type_get(redir, &file))
	// TODO: pass proper length of string maybe.
		error_syntax(redir->str);
	value = (t_token *) arr_get(tokens, (*index)++);
	// TODO: check for invalid tokens after redirection like operators and parentheses.
	if (file.type == FILE_IN_HEREDOC)
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