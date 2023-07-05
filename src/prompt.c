/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:54:46 by christianme       #+#    #+#             */
/*   Updated: 2023/07/04 12:01:26 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char *ft_prompt(void)
void ft_prompt(void)
{
	char* input;
	using_history();

	while (1) {
		ft_signals();
		input = readline(">>");
		if (input == NULL)
			break;
		if (input[0] != '\0')
			add_history(input);

		// Tests //
		// printf("input:  %s\n", input);

		// ft_exit();

		// char* path = "src_man";
		// printf("path:   %s\n", path);
		// ft_cd(path);

		// ft_env();
		// ft_pwd();
		// free(input);
		// return (input);
	}

}