#include "minishell.h"
#include "str.h"

int	cmd_is_external(t_command *cmd)
{
	return (cmd->type == COMMAND_EXTERNAL);
}

int	is_local_script(char *cmd)
{
	return (str_starts_with(cmd, "/")
		|| str_starts_with(cmd, "./") || str_starts_with(cmd, "../"));
}
