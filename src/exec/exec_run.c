/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:50:33 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:50:34 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "error.h"
#include "global.h"
#include "fd.h"

static void	exec_cmd(t_command *cmd)
{
	if (cmd_is_external(cmd))
		exec_external(cmd);
	else
		error(exec_builtin(cmd));
}

void	run_child(t_command *cmd, int input, int ports[2], int last)
{
	if (!last)
		fd_close(ports[0]);
	if (redirect(cmd, input, ports, last))
		error_fatal();
	exec_cmd(cmd);
}

void	run_parent(t_command *cmd, int *fd, int ports[2])
{
	(void) cmd;
	fd_close(ports[1]);
	if (*fd != 0)
		fd_close(*fd);
	*fd = ports[0];
}

int	run_builtin_in_main(t_command *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (super_duper(cmd->fd_out, STDOUT_FILENO))
			error_fatal();
	}
	return (exec_builtin(cmd));
}
