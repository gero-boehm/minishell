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

#include <stdio.h>
#include "minishell.h"
#include "global.h"
#include "arraydef.h"
#include "sequence.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_array	sequence;

	input = NULL;
	(void) argc;
	(void) argv;
	global_init();
	signals();

	// *------TEST------*
	// char *cmd_args[] = {"ls", NULL , NULL};
	sequence_factory(F_SINGLE_CHAIN_SINGLE_EXTERNAL, &sequence);
	sequence_print(&sequence);

	int i = 0;
	// *----------------*

	while (1)
	{
		if (prompt(&input))
			break ;
		// ft_parse get_cmd_args //
		if (i < 1)
			exec(&sequence);
		i++;
	}


	// *--EXECV--*
	// char *cmd_args[] = {"ls", "-l" , NULL};
	// ft_exec(cmd_args);
	// printf("exec: %i\n", ft_exec(cmd_args));
	// printf("path: %s\n", cmd_path);
	// *--PROMPT--*
	error(0);
	cleanup();
	return (0);
}
