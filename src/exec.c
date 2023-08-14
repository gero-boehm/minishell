// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/26 09:53:10 by christianme       #+#    #+#             */
// /*   Updated: 2023/07/24 19:53:49 by gbohm            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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


// void	print_environ(void)
// {
// 	while (*environ != NULL)
// 		printf("%s\n", *environ++);
// }

static int	ft_get_cmd_path(char **paths, char *cmd, char *cmd_path)
{
	while (*paths != NULL)
	{
		//TODO: replace sprintf
		sprintf(cmd_path, "%s/%s", *paths++, cmd);
		if (!access(cmd_path, X_OK))
			return (0);
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

int	exec_cmd(t_command *command)
{
	char		*paths_str;
	char		**paths;
	char		**env;
	char		*cmd_path;

	cmd_path = malloc(100);
	if (command->type == COMMAND_EXTERNAL)
	{
		// printf("%s\n",  command->data.external.args[0]);
		//TODO: find proper exit code
		if (env_get_all(&env))
			error(2);
		if (env_get("PATH", &paths_str))
			return (1);
		paths = ft_split(paths_str, ':');
		if (!ft_get_cmd_path(paths, command->data.external.args[0], cmd_path))
			execve(cmd_path, command->data.external.args, env);
	}
	else
		exec_builtin(command);
	return (0);
}

int	run_child(t_command *command, int ports[2])
{
	close(ports[0]);
	dup2("fd", STDIN);
	dup2(ports[1], STDOUT);
	close("fd");
	close(ports[1]);
	if ("fd" == -1)
		return ;
	exec_cmd(command);
}

int	run_parent(t_command *command, int ports[2])
{
	close(ports[1]);
	close("fd");
	"fd" = ports[0];
}

//TODO mem_alloc amount_cmds
int	exec(t_array *sequence)
{
	pid_t		*pid;
	int			ports[2];
	int			i;
	int			amount_cmds;
	// int			amount_chains;
	t_chain		*chain;
	t_command	*command;

	chain = (t_chain *) arr_get(sequence, 0);
	command = (t_command *) arr_get(&chain->commands, 0);
	amount_cmds = arr_size(&chain->commands);
	i = 0;
	// amount_chains = arr_size(sequence);
	// pid = malloc(amount_cmds);
	// go through seqence, amount of chains
	// goes though chain, check and execute external or builtin
	while (i < amount_cmds)
	{
		if (amount_cmds - 1 > i)
			if (pipe(ports) == -1)
				perror("pipe failed");
		pid[i] = fork();
		if (pid[i] == -1)
			perror("fork failed");
		if (pid[i] == 0)
			run_child(command, ports);
		else
			run_parent(command, ports);
		i++;
	}
	//----------Parent process--------//
	wait(NULL);
	int status;
	waitpid(pid[0], &status, NULL);
	//--------------------------------//
	close("fd");
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

	// printf("op: %i\n", chain->op);
	// printf("Amount chains: %i\n", amount_chains);

	// int amount_chains = arr_size(sequence);
	// int amount_cmds = arr_size(chain);
	// int	id_chain = 0;
	// int	id_cmd = 0;



	// if (command->type == COMMAND_EXTERNAL)
	// {
	// 	// printf("%s\n",  command->data.external.args[0]);
	// 	//TODO: find proper exit code
	// 	if (env_get_all(&env))
	// 		error(2);
	// 	if (env_get("PATH", &paths_str))
	// 		return (1);
	// 	paths = ft_split(paths_str, ':');
	// 	if (!ft_get_cmd_path(paths, command->data.external.args[0], cmd_path))
	// 		execve(cmd_path, command->data.external.args, env);
	// }
	// else
	// 	exec_builtin(command);

	// if (env_get("PATH", &paths_str))
	// 	return (1);
	// paths = ft_split(paths_str, ':');

	// pid = fork();
	// if (pid > 0)
	// {
	// 	write(1, "This is the parent process\n---------------\n", 44);
	// 	wait(NULL);
	// }
	// else if (pid == 0)
	// {
	// 	write(1, "This is the child process\n---------------\n", 43);
	// 	// if (is_builtin(cmd_args[0]))
	// 	// 	exec_builtin(cmd_args[0]);
	// 	// if (env_get_all(&env))
	// 	// 	// TODO: find proper exit code
	// 	// 	error(2);
	// 	// else if (!ft_get_cmd_path(paths, cmd_args[0], cmd_path))
	// 	// 	execve(cmd_path, cmd_args, env);
	// }
	// else
	// 	perror("fork failed");
