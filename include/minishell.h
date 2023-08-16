/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:05 by cmeng             #+#    #+#             */
/*   Updated: 2023/08/16 18:07:17 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "libft.h"
# include "arraydef.h"
# include "cmddef.h"

int		prompt(char **input);
int		exec_chain(t_chain *chain);

void	signals(void);
void	ctrlc(int sig);

#endif
