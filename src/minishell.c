/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:02:18 by cmeng             #+#    #+#             */
/*   Updated: 2023/08/25 16:01:49 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "global.h"
#include "arraydef.h"
#include "sequence.h"
#include "array.h"
#include "error.h"
#include "str.h"

void	exec_sequence(t_array *sequence)
{
	unsigned long	i;
	int				last_return_chain;
	t_chain			*chain;

	i = 0;
	while (i < arr_size(sequence))
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

	// long n;

	// printf("%d | %ld\n", str_to_long_unsafe("5684", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("-1", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("2147483647", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("2147483648", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("-2147483648", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("-2147483649", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("-2147483649466", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("-d", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("-+5", &n), n);
	// printf("%d | %ld\n", str_to_long_unsafe("+5", &n), n);
	// *------RETURN PARSER------*
	// char *cmd_args[] = {"ls", NULL , NULL};
	// sequence_factory(F_SINGLE_CHAIN_SINGLE_EXTERNAL, &sequence);
	// sequence_factory(F_SINGLE_CHAIN_SINGLE_BUILTIN, &sequence);
	// sequence_factory(F_SINGLE_CHAIN_MULTIPLE_EXTERNAL, &sequence);
	// sequence_factory(F_SINGLE_CHAIN_MULTIPLE_EXTERNAL_AND_BUILTINS, &sequence);

	// sequence_factory(F_MULTIPLE_CHAINS_SINGLE_EXTERNAL, &sequence);
	// sequence_factory(F_MULTIPLE_CHAINS_SINGLE_EXTERNAL_AND_BUILTINS, &sequence);
	// sequence_factory(F_MULTIPLE_CHAINS_MULTIPLE_EXTERNAL_AND_BUILTINS, &sequence);
	// sequence_factory(F_MULTIPLE_CHAINS_ALL_BUILTINS, &sequence);

	// // sequence_print(&sequence);
	// // *----------------*
	// while (1)
	// {
	// 	// prompt(&input);
	// 	if (prompt(&input))
	// 		break ;
	// 	// ft_parse (&input, &sequence) //
	// 	exec_sequence(&sequence);
	// }


	// *--EXECV--*
	// char *cmd_args[] = {"ls", "-l" , NULL};
	// ft_exec(cmd_args);
	// printf("exec: %i\n", ft_exec(cmd_args));
	// printf("path: %s\n", cmd_path);
	// *--PROMPT--*
	cleanup();
	return (0);
}
