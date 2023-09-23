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
	if (token_is_pipe(token))
		return ((*index)++, 1);
	if (token_is_operator(token))
		return (1);
	if (token_is_parenthesis_closing(token))
		return ((*index)++, 1);
	return (0);
}

static void	parse_command_init(t_raw_command *command)
{
	if (arr_create(&command->args, sizeof(char *)))
		error_fatal();
	if (arr_create(&command->files, sizeof(t_file)))
		error_fatal();
	if (arr_create(&command->vars_args, sizeof(t_range)))
		error_fatal();
	if (arr_create(&command->vars_files, sizeof(t_range)))
		error_fatal();
}

static int	parse_command_execute(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_token	*token;

	token = (t_token *) arr_get(tokens, *index);
	if (token_is_possibly_parenthesis(token))
		return (parser_subsequence_parse(tokens, index, command));
	if (token_is_possibly_redir(token))
		return (parser_redir_parse(tokens, index, command));
	parser_vars_copy(token, arr_size(&command->args), &command->vars_args);
	if (arr_add(&command->args, &token->str))
		error_fatal();
	(*index)++;
	return (0);
}

void	parser_command_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	parse_command_init(command);
	while (1)
	{
		if (parse_command_execute(tokens, index, command))
			return (2);
		if (command_end(tokens, index))
			return ;
	}
}
