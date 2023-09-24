#include "cmddef.h"
#include "rangedef.h"
#include "array.h"
#include "token.h"
#include "parser.h"
#include "error.h"

static int	command_end(t_array *tokens, unsigned long *index)
{
	t_token	*token;

	if (*index >= arr_size(tokens))
		return (1);
	token = (t_token *) arr_get(tokens, *index);
	if (token_is(token, TOKEN_PIPE))
		return ((*index)++, 1);
	if (token_is_any(token, TOKEN_OPERATOR | TOKEN_CLOSING))
		return (1);
	return (0);
}

static int	parse_command_init(t_raw_command *command)
{
	if (arr_create(&command->args, sizeof(char *)))
		return (1);
	if (arr_create(&command->files, sizeof(t_file)))
		return (2);
	if (arr_create(&command->vars_args, sizeof(t_range)))
		return (3);
	if (arr_create(&command->vars_files, sizeof(t_range)))
		return (4);
	return (0);
}

static int	parse_command_execute(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_token	*token;

	token = (t_token *) arr_get(tokens, *index);
	if (token_is(token, TOKEN_OPENING))
		return (parser_subsequence_parse(tokens, index, command));
	if (token_is(token, TOKEN_REDIRECTION))
		return (parser_redir_parse(tokens, index, command));
	if (parser_vars_copy(token, arr_size(&command->args), &command->vars_args))
		return (2);
	if (arr_add(&command->args, &token->str))
		return (3);
	(*index)++;
	return (0);
}

int	parser_command_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	if (parse_command_init(command))
		return (1);
	while (1)
	{
		if (parse_command_execute(tokens, index, command))
			return (2);
		if (command_end(tokens, index))
			break ;
	}
	return (0);
}
