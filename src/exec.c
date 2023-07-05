/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:53:10 by christianme       #+#    #+#             */
/*   Updated: 2023/07/05 15:10:42 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;

void	print_environ(void)
{
	while (*environ != NULL)
		printf("%s\n", *environ++);
}

static int	ft_get_cmd_path(char **paths, char *cmd, char *cmd_path)
{
	while (*paths != NULL)
	{
		sprintf(cmd_path, "%s/%s", *paths++, cmd);
		// printf("path: %s\n", path);
		if (!access(cmd_path, X_OK))
			return (0);
	}
	return (1);
}

int	ft_exec(char **cmd_args)
{
	char	*env;
	char	**paths;
	char	*cmd_path = malloc(100);

	env = getenv("PATH");
	paths = ft_split(env, ':');
	if (ft_get_cmd_path(paths, cmd_args[0], cmd_path))
		return (1);
	// //*--Create Child process before execve--*
	// // printf("cmd of execve: %s\n", cmd_args[0]);
	// // printf("cmd_path: %s\n", cmd_path);
	// int		pid;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	printf("This is the child process\n");
	// 	execve(cmd_path, cmd_args, environ);
	// }
	// else
	// 	printf("This is the parent process\n---------------\n");
	*environ = "***TESTEDIT***";
	print_environ();
	// perror("fail");
	// printf("yay %d\n", errno);
	return (0);
}


// int ft_exec(char *path, char *str)
// {
// 	char *env;
// 	char **paths;
// 	// char *validpath;

// 	env = getenv("PATH=");
// 	paths = ft_split(env, ':');
// 	// printf("env: %s\n:" ,env);
// 	// print(paths);

// 	// char *path = malloc(100);

// 	sprintf(path, "%s/%s", paths[0], str);
// 	// validpath = ft_strjoin(paths[0], "/echo");

// 	// printf("Valid[0]: %s\n", paths[0]);
// 	printf("Valid: %s\n", path);

// 	return(0);
// }