#include <stdio.h>
#include <readline/readline.h>
#include "cmddef.h"
#include "rangedef.h"
#include "parser.h"
#include "array.h"
#include "token.h"
#include "str.h"
#include "vars.h"

static void	parser_redir_type_get(t_token *token, t_file *file)
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

static int	parser_redir_heredoc(t_heredoc *heredoc, t_token *delimiter)
{
	t_array	lines;
	char	*line;

	if (arr_create(&heredoc->vars, sizeof(t_range)))
		return (1);
	if (arr_create(&lines, sizeof(char *)))
		return (2);
	while (1)
	{
		// TODO: this allocation is not caught by custom memory handler. write function that adds pointers to allocs array
		line = readline("> ");
		if (line == NULL || str_eq(line, delimiter->str))
			break ;
		if (arr_add(&lines, &line))
			return (3);
	}
	if (str_from_arr(&lines, "\n", &heredoc->str))
		return (4);
	arr_free_ptr(&lines);
	if (delimiter->contained_quotes)
		return (0);
	if (vars_extract(heredoc->str, 0, 0, &heredoc->vars))
		return (5);
	return (0);
}

int	parser_redir_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_token	*redir;
	t_token	*value;
	t_file	file;

	redir = (t_token *) arr_get(tokens, (*index)++);
	value = (t_token *) arr_get(tokens, (*index)++);
	parser_redir_type_get(redir, &file);
	if (file.type == FILE_HEREDOC)
	{
		if (parser_redir_heredoc(&file.data.heredoc, value))
			return (1);
	}
	else
	{
		if (parser_vars_copy(value, arr_size(&command->files), &command->vars_files))
			return (2);
		if (str_dup(value->str, &file.data.path))
			return (3);
	}
	return (arr_add(&command->files, &file) * 4);
}