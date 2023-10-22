#include <unistd.h>
#include "minishell.h"
#include "fd.h"

int	super_duper(int fd_src, int fd_dst)
{
	if (dup2(fd_src, fd_dst) == -1)
	{
		fd_close(fd_src);
		return (1);
	}
	fd_close(fd_src);
	return (0);
}

int	redirect(t_command *cmd, int input, int ports[2], int last)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (super_duper(cmd->fd_in, STDIN_FILENO))
			return (1);
	}
	else if (input != STDIN_FILENO)
	{
		if (super_duper(input, STDIN_FILENO))
			return (2);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (super_duper(cmd->fd_out, STDOUT_FILENO))
			return (3);
	}
	else if (!last)
	{
		if (super_duper(ports[1], STDOUT_FILENO))
			return (4);
	}
	return (0);
}
