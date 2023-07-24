// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minishell.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/12 08:59:40 by christianme       #+#    #+#             */
// /*   Updated: 2023/07/20 18:10:40 by cmeng            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdio.h>
// #include "minishell.h"
// #include "global.h"


// int	main(int argc, char **argv)
// {
// 	char	*input;

// 	global_init();
// 	input = NULL;
// 	(void) argc;
// 	(void) argv;
// 	// *------TEST------*
// 	char *cmd_args[] = {"ls", NULL , NULL};
// 	int i = 0;
// 	// *----------------*

// 	signals();
// 	while (1)
// 	{
// 		if (prompt(&input))
// 			break ;
// 		// ft_parse get_cmd_args //
// 		if (i < 1)
// 			exec(cmd_args);
// 		i++;
// 	}


// 	// *--EXECV--*
// 	// char *cmd_args[] = {"ls", "-l" , NULL};
// 	// ft_exec(cmd_args);
// 	// printf("exec: %i\n", ft_exec(cmd_args));
// 	// printf("path: %s\n", cmd_path);
// 	// *--PROMPT--*
// 	return (0);
// }