/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:51:02 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:02 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "minishell.h"
#include "error.h"
#include "global.h"
#include "str.h"
#include "memory.h"

int	prompt(char **input)
{
	char	*str;

	using_history();
	*input = readline("miniheaven$ ");
	mem_add(*input);
	if (*input == NULL)
	{
		if (str_join(&str, "", "\x1b[1A\r", shell_name(), "$ exit\n", NULL))
			error_fatal();
		write(2, str, str_len(str));
		success();
	}
	if (*input[0] != '\0')
		add_history(*input);
	return (0);
}
