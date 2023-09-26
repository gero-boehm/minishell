#include "cmddef.h"
#include "converter.h"
#include "array.h"
#include "str.h"
#include "vars.h"

static void	converter_command_type_get(t_raw_command *raw_command, t_command *command)
{
	char	*arg;

	arg = *(char **) arr_get(&raw_command->args, 0);
	if (str_eq(arg, "echo"))
		command->type = COMMAND_BUILTIN_ECHO;
	else if (str_eq(arg, "cd"))
		command->type = COMMAND_BUILTIN_CD;
	else if (str_eq(arg, "pwd"))
		command->type = COMMAND_BUILTIN_PWD;
	else if (str_eq(arg, "export"))
		command->type = COMMAND_BUILTIN_EXPORT;
	else if (str_eq(arg, "unset"))
		command->type = COMMAND_BUILTIN_UNSET;
	else if (str_eq(arg, "env"))
		command->type = COMMAND_BUILTIN_ENV;
	else if (str_eq(arg, "exit"))
		command->type = COMMAND_BUILTIN_EXIT;
	else
		command->type = COMMAND_EXTERNAL;
}

static int	converter_exapand_vars(t_raw_command *raw_command)
{
	unsigned long	i;
	char			**arg;

	i = 0;
	while (i < arr_size(&raw_command->args))
	{
		arg = (char **) arr_get(&raw_command->args, i);
		if (vars_expand_str(&raw_command->vars_args, i, arg))
			return (1);
		i++;
	}
	return (0);
}

int converter_convert(t_raw_command *raw_command, t_command *command)
{
	converter_command_type_get(raw_command, command);
	command->fd_in = 0;
	command->fd_out = 1;
	if (converter_exapand_vars(raw_command))
		return (1);
	if (command->type == COMMAND_BUILTIN_ECHO)
		return (converter_convert_builtin_echo(raw_command, &command->data.builtin_echo));
	if (command->type == COMMAND_BUILTIN_CD)
		return (converter_convert_builtin_cd(raw_command, &command->data.builtin_cd));
	if (command->type == COMMAND_BUILTIN_EXPORT)
		return (converter_convert_builtin_export(raw_command, &command->data.builtin_export));
	if (command->type == COMMAND_BUILTIN_UNSET)
		return (converter_convert_builtin_unset(raw_command, &command->data.builtin_unset));
	if (command->type == COMMAND_BUILTIN_EXIT)
		return (converter_convert_builtin_exit(raw_command, &command->data.builtin_exit));
	if (command->type == COMMAND_EXTERNAL)
		return (converter_convert_external(raw_command, &command->data.external));
	return (0);
}