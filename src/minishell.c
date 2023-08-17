/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:02:18 by cmeng             #+#    #+#             */
/*   Updated: 2023/08/17 07:59:08 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "global.h"
#include "arraydef.h"
#include "sequence.h"
#include "array.h"

void	exec_sequence(t_array *sequence)
{
	int		i;
	int		last_return_chain;
	int		amount_chains;
	t_chain	*chain;

	i = 0;
	last_return_chain = 0;
	amount_chains = arr_size(sequence);
	while (i < amount_chains)
	{
		chain = (t_chain *)arr_get(sequence, i);
		last_return_chain = exec_chain(chain);
		if (chain->op == OP_AND)
			if (last_return_chain)
				error(0);
		if (chain->op == OP_OR)
			if (!last_return_chain)
				error(0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*input;
	t_array	sequence;

	input = NULL;
	(void) argc;
	(void) argv;
	global_init();
	signals();
	// *------RETURN PARSER------*
	// char *cmd_args[] = {"ls", NULL , NULL};
	sequence_factory(F_SINGLE_CHAIN_SINGLE_EXTERNAL, &sequence);
	// sequence_print(&sequence);
	// *----------------*
	while (1)
	{
		if (prompt(&input))
			break ;
		// ft_parse (&input, &sequence) //
		exec_sequence(&sequence);
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
