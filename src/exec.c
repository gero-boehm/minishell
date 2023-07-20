/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:53:10 by christianme       #+#    #+#             */
/*   Updated: 2023/07/20 13:30:09 by cmeng            ###   ########.fr       */
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

int	is_builtin(char *cmd)
{
	return (ft_strncmp("echo", cmd, ft_strlen("echo")) == 0
		|| ft_strncmp("cd", cmd, ft_strlen("cd")) == 0
		|| ft_strncmp("pwd", cmd, ft_strlen("pwd")) == 0
		|| ft_strncmp("export", cmd, ft_strlen("export")) == 0
		|| ft_strncmp("unset", cmd, ft_strlen("unset")) == 0
		|| ft_strncmp("env", cmd, ft_strlen("env")) == 0
		|| ft_strncmp("exit", cmd, ft_strlen("exit")) == 0);
}

void	exec_builtin(char *cmd)
{
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		printf("Builtin: %s executed\n", cmd);
		// ft_echo();
	else if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		printf("Builtin: %s executed\n", cmd);
		// ft_cd();
	else if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		printf("Builtin: %s executed\n", cmd);
		// ft_pwd():
	else if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		printf("Builtin: %s executed\n", cmd);
		// ft_export();
	else if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		printf("Builtin: %s executed\n", cmd);
		// ft_unset();
	else if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
	{
		printf("Builtin: %s executed\n", cmd);
		exit(1);
	}
		// ft_env();
	else if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		printf("Builtin: %s executed\n", cmd);
		// ft_exit();

}

int	ft_exec(char **cmd_args)
{
	char	*env;
	char	**paths;
	char	*cmd_path = malloc(100);
	int		pid;

	env = getenv("PATH");
	paths = ft_split(env, ':');

	pid = fork();
	if (pid > 0)
	{
		write(1, "This is the parent process\n---------------\n", 44);
		wait(NULL);
	}
	else if (pid == 0)
	{
		write(1, "This is the child process\n---------------\n", 43);
		if (is_builtin(cmd_args[0]))
			exec_builtin(cmd_args[0]);
		else if (!ft_get_cmd_path(paths, cmd_args[0], cmd_path))
			execve(cmd_path, cmd_args, environ);
	}
	else
		perror("fork failed");
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