/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:53:10 by christianme       #+#    #+#             */
/*   Updated: 2023/07/03 14:18:04 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>

static int ft_get_cmd_path(char **paths, char *cmd, char *cmd_path)
{
	while (*paths != NULL)
	{
		sprintf(cmd_path, "%s/%s", *paths++, cmd);
		// printf("path: %s\n", path);
		if (access(cmd_path, X_OK))
			return(0);
	}
	return (1);
}

int ft_exec(char **cmd_args)
{
	char *env;
	char **paths;
	char *cmd_path = malloc(100);

	env = getenv("PATH");
	paths = ft_split(env, ':');
	if (ft_get_cmd_path(paths, cmd_args[0], cmd_path))
		return (1);
		
	//*--Create Child process before execve--*
	execve(cmd_path, cmd_args, NULL);
	printf("yay %d\n", errno);
	return (0);
}


// void print(char **paths)
// {
// 	while(*paths != NULL)
// 		printf("Path: %s\n", *paths++);
// }

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