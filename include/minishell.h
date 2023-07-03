/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:00:16 by christianme       #+#    #+#             */
/*   Updated: 2023/07/03 14:12:04 by cmeng            ###   ########.fr       */
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
int 	ft_exec(char **cmd_args);

void    ft_signals(void);
void    ft_ctrlc(int sig);
void    ft_exit(void);

int     ft_pwd(void);
int     ft_echo(int n, char *str);
int     ft_env(void);
int     ft_cd(char *str);

