/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 08:59:40 by christianme       #+#    #+#             */
/*   Updated: 2023/07/20 13:29:09 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;

	input = NULL;
	(void) argc;
	(void) argv;
	// *------TEST------*
	char *cmd_args[] = {"ls", NULL , NULL};
	int i = 0;
	// *----------------*

	ft_signals();
	while (1)
	{
		if (ft_prompt(&input))
			break ;
		// ft_parse get_cmd_args //
		if (i < 1)
			ft_exec(cmd_args);
		i++;
	}


	// *--EXECV--*
	// char *cmd_args[] = {"ls", "-l" , NULL};
	// ft_exec(cmd_args);
	// printf("exec: %i\n", ft_exec(cmd_args));
	// printf("path: %s\n", cmd_path);
	// *--PROMPT--*
	return (0);
}