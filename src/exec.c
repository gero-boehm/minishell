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


// void	print_environ(void)
// {
// 	while (*environ != NULL)
// 		printf("%s\n", *environ++);
// }

static int	ft_get_cmd_path(char **paths, char *cmd, char *cmd_path)
{
	while (*paths != NULL)
	{
		//replace printf
		sprintf(cmd_path, "%s/%s", *paths++, cmd);
		// printf("path: %s\n", path);
		if (!access(cmd_path, X_OK))
			return (0);
	}
	return (1);
}

// int	exec(char **cmd_args)
int	exec(t_array *sequence)
{
	char	*paths_str;
	char	**paths;
	char	**env;
	char	*cmd_path = malloc(100);
	int		pid;


	// go through seqence, amount of chains = childs
	// go though chain, check external or builtin

	int amount_chains = arr_size(sequence);


	if (env_get("PATH", &paths_str))
		return (1);
	paths = ft_split(paths_str, ':');

	pid = fork();
	if (pid > 0)
	{
		write(1, "This is the parent process\n---------------\n", 44);
		wait(NULL);
	}
	else if (pid == 0)
	{
		write(1, "This is the child process\n---------------\n", 43);
		// if (is_builtin(cmd_args[0]))
		// 	exec_builtin(cmd_args[0]);
		// if (env_get_all(&env))
		// 	// TODO: find proper exit code
		// 	error(2);
		// else if (!ft_get_cmd_path(paths, cmd_args[0], cmd_path))
		// 	execve(cmd_path, cmd_args, env);
	}
	else
		perror("fork failed");
	return (0);
}



// int	is_builtin(char *cmd)
// {
// 	return (ft_strncmp("echo", cmd, ft_strlen("echo")) == 0
// 		|| ft_strncmp("cd", cmd, ft_strlen("cd")) == 0
// 		|| ft_strncmp("pwd", cmd, ft_strlen("pwd")) == 0
// 		|| ft_strncmp("export", cmd, ft_strlen("export")) == 0
// 		|| ft_strncmp("unset", cmd, ft_strlen("unset")) == 0
// 		|| ft_strncmp("env", cmd, ft_strlen("env")) == 0
// 		|| ft_strncmp("exit", cmd, ft_strlen("exit")) == 0);
// }

// void	exec_builtin(char *cmd)
// {
// 	if (ft_strncmp("echo", cmd, ft_strlen("echo")) == 0)
// 		builtin_echo();
// 	else if (ft_strncmp("cd", cmd, ft_strlen("cd")) == 0)
// 		builtin_cd();
// 	else if (ft_strncmp("pwd", cmd, ft_strlen("pwd")) == 0)
// 		builtin_pwd();
// 	else if (ft_strncmp("export", cmd, ft_strlen("export")) == 0)
// 		builtin_export();
// 	else if (ft_strncmp("unset", cmd, ft_strlen("unset")) == 0)
// 		builtin_unset();
// 	else if (ft_strncmp("env", cmd, ft_strlen("env")) == 0)
// 		builtin_env();
// 	else if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
// 		builtin_exit();
// 	error(0);
// }