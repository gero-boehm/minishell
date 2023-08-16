/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:05:20 by cmeng             #+#    #+#             */
/*   Updated: 2023/08/16 18:05:24 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"
#include "env.h"
#include "global.h"
#include "builtins.h"
#include "array.h"
#include "cmddef.h"
#include "str.h"

// void	print_environ(void)
// {
// 	while (*environ != NULL)
// 		printf("%s\n", *environ++);
// }

static int	get_cmd_path(t_array *paths, char *cmd, char *cmd_path)
{
	while (paths->elements != NULL)
	{
		if (str_join(&cmd_path, "", *paths, "/", cmd, NULL))
			return (1);
		if (!access(cmd_path, X_OK))
			return (0);
		paths++;
	}
	return (1);
}

void	exec_builtin(t_command *command)
{
	if (command->type == COMMAND_BUILTIN_ECHO)
		builtin_echo(&command->data.builtin_echo);
	else if (command->type == COMMAND_BUILTIN_CD)
		builtin_cd(&command->data.builtin_cd);
	else if (command->type == COMMAND_BUILTIN_PWD)
		builtin_pwd();
	else if (command->type == COMMAND_BUILTIN_EXPORT)
		builtin_export(&command->data.builtin_export);
	else if (command->type == COMMAND_BUILTIN_UNSET)
		builtin_unset(&command->data.builtin_unset);
	else if (command->type == COMMAND_BUILTIN_ENV)
		builtin_env();
	else if (command->type == COMMAND_BUILTIN_EXIT)
		builtin_exit();
}

int	exec_cmd(t_command *cmd)
{
	char		*paths_str;
	t_array		paths;
	char		**env;
	char		*cmd_path;

	if (cmd->type == COMMAND_EXTERNAL)
	{
		//TODO: find proper exit code
		if (env_get_all(&env))
			error(134);
		if (env_get("PATH", &paths_str))
			error(134);
		if (str_split(paths_str, ':', &paths))
			error(134);
		if (!get_cmd_path(&paths, cmd->data.external.args[0], cmd_path))
			execve(cmd_path, cmd->data.external.args, env);
	}
	else
		exec_builtin(cmd);
	return (0);
}

int	run_child(t_command *cmd, int port)
{
	// close(ports[0]);
	// dup2("fd", STDIN);
	// dup2(ports[1], STDOUT);
	// close("fd");
	// close(ports[1]);
	// if ("fd" == -1)
	// 	return ;
	exec_cmd(cmd);
}

int	run_parent(t_command *command, int port)
{
	// close(ports[1]);
	// close("fd");
	// "fd" = ports[0];
}

//TODO mem_alloc amount_cmds
int	exec_chain(t_chain *chain)
{
	pid_t			pid;
	int				ports[2];
	int				i;
	int				amount_cmds;
	// t_raw_command	*raw;
	t_command		*cmd;

	amount_cmds = arr_size(&chain->commands);
	i = 0;
	while (i < amount_cmds)
	{
		cmd = (t_command *) arr_get(&chain->commands, i);
		// raw = (t_raw_command *) arr_get(&chain->commands, i);
		// cmd = 2nd_parse(raw);
		// if (amount_cmds - 1 > i)
		// 	if (pipe(ports) == -1)
		// 		perror("pipe failed");
		pid = fork();
		if (pid == -1)
			perror("fork failed");
		if (pid == 0)
			run_child(cmd, ports[1]);
		else
			run_parent(cmd, ports[0]);
		i++;
	}
	//----------Parent process--------//
	// wait(NULL);
	// int status;
	// waitpid(pid[0], &status, NULL);
	//--------------------------------//
	// close("fd");
	error(0);
	return (0);
}

/*--------------sequence tools--------------------------*/
	// int amount_chains = arr_size(sequence);
	// t_chain	*chain;
	// chain = (t_chain *) arr_get(sequence, 0);
	// t_command	*command;
	// command = (t_command *) arr_get(&chain->commands, 0);
	// if (command->type == COMMAND_EXTERNAL)
	// 	command->data.external.cmd;
	// if (command->type == COMMAND_CD)
	// 	command->data.builtin_cd.path;
/*------------------------------------------------------*/
