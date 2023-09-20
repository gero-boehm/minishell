#include "cmddef.h"
#include "rangedef.h"
#include "array.h"
#include "token.h"

static int	command_end(t_array *tokens, unsigned long *index)
{
	t_token	*token;

	if (*index >= arr_size(tokens))
		return (1);
	token = (t_token *) arr_get(tokens, *index);
	if (token_is_pipe(token))
		return ((*index)++, 1);
	return (token_is_operator(token));
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

// static int	parse_command_redir(t_array *tokens, unsigned long *index, t_raw_command *command)
// {

// }

static int	parser_command_copy_vars_args(t_token *token, t_raw_command *command)
{
	unsigned long	i;
	t_range			*var;

	i = 0;
	while (i < arr_size(&token->vars))
	{
		var = (t_range *) arr_get(&token->vars, i);
		var->meta.var_data.index = arr_size(&command->args);
		if (arr_add(&command->vars_args, var))
			return (1);
		i++;
	}
	return (0);
}

static int	parser_command_copy_vars_files(t_token *token, t_raw_command *command)
{
	unsigned long	i;
	t_range			*var;

	i = 0;
	while (i < arr_size(&token->vars))
	{
		var = (t_range *) arr_get(&token->vars, i);
		var->meta.var_data.index = arr_size(&command->files);
		if (arr_add(&command->vars_files, var))
			return (1);
		i++;
	}
	return (0);
}

static int	parser_command_parse_redir(t_token *token, t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_file	file;

	if (token_is_redir_in(token))
		file.type = FILE_IN;
	(*index)++;
	token = (t_token *) arr_get(tokens, *index);
	file.path = token->str;
	if (parser_command_copy_vars_files(token, command))
		return (1);
	if (arr_add(&command->files, &file))
		return (2);
	(*index)++;
	return (0);
}

static int	parse_command_execute(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_token	*token;

	token = (t_token *) arr_get(tokens, *index);
	if (token_is_redir(token))
		return (parser_command_parse_redir(token, tokens, index, command));
	if (parser_command_copy_vars_args(token, command))
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
			return (0);
	}
	return (0);
}
