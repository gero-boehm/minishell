/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:33:14 by christianme       #+#    #+#             */
/*   Updated: 2023/06/19 15:25:32 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_signals(void)
{
    signal(SIGINT, &ft_ctrlc);
    signal(SIGQUIT, SIG_IGN);
}
void    ft_ctrlc(int sig)
{
    if (sig == SIGINT)
    {
        // printf("%i %s", "\n");
        write(STDERR_FILENO, "\n", 1);
		// rl_replace_line(">>", 0);
		// rl_on_new_line();
		// rl_redisplay();
    }
}

void    ft_exit(void)
{
        printf("%s\n", "exit");
        clear_history();
        exit(0);
}