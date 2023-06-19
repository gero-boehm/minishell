/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:00:16 by christianme       #+#    #+#             */
/*   Updated: 2023/06/19 15:24:59 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>


void    ft_prompt(void);
int     ft_pwd(void);
int     ft_echo(int n, char *str);
int     ft_env(void);
int     ft_cd(char *str);

void    ft_signals(void);
void    ft_ctrlc(int sig);
void    ft_exit(void);


