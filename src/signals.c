/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:33:14 by christianme       #+#    #+#             */
/*   Updated: 2023/07/20 13:30:56 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals(void)
{
	signal(SIGINT, &ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	ft_exit(void)
// {
// 	printf("%s\n", "exit");
// 	clear_history();
// 	exit(0);
// }