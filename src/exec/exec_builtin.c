#include <stdio.h>
#include "builtins.h"

int	exec_builtin(t_command *command)
{
	if (command->type == COMMAND_BUILTIN_ECHO)
		return (builtin_echo(&command->data.builtin_echo));
	else if (command->type == COMMAND_BUILTIN_CD)
		return (builtin_cd(&command->data.builtin_cd));
	else if (command->type == COMMAND_BUILTIN_PWD)
		return (builtin_pwd());
	else if (command->type == COMMAND_BUILTIN_EXPORT)
		return (builtin_export(&command->data.builtin_export));
	else if (command->type == COMMAND_BUILTIN_UNSET)
		return (builtin_unset(&command->data.builtin_unset));
	else if (command->type == COMMAND_BUILTIN_ENV)
		return (builtin_env());
	else if (command->type == COMMAND_BUILTIN_EXIT)
		return (builtin_exit(&command->data.builtin_exit));
	printf("(⊃｡•́‿•̀｡)⊃\n");
	return (127);
}
