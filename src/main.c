/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:59:13 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 18:20:21 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "array.h"
#include "env.h"
#include "error.h"
#include "minishell.h"
#include "deserializer.h"
#include "fd.h"
#include "memory.h"

static void	run(char *input)
{
	t_array			sequence;

	if (parse_input(input, &sequence))
	{
		fd_close_all();
		return ;
	}
	exec_sequence(&sequence);
	fd_close_all();
}

static int	run_subshell(char *str)
{
	t_array			sequence;

	if (deserializer_deserialize(str, &sequence))
		error_fatal();
	printf("");
	exec_sequence(&sequence);
	cleanup();
	return (global()->exit_code);
}

static void	infinite_read(char **input)
{
	while (1)
	{
		if (read_input(input))
			break ;
		run(*input);
	}
}

static void	infinite_prompt(char **input)
{
	while (1)
	{
		if (prompt(input))
			break ;
		run(*input);
	}
}

int	main(int argc, char **argv)
{
	char	*input;

	input = NULL;
	global_init(argv[0]);
	signals();
	if (argc == 2 && !env_get("--mhss", NULL))
		return (run_subshell(argv[1]));
	if (argc > 1)
		return (cleanup(), return_too_many_args(0));
	if (!isatty(STDIN_FILENO))
	{
		infinite_read(&input);
		cleanup();
		return (global()->exit_code);
	}
	infinite_prompt(&input);
	cleanup();
	return (0);
}
