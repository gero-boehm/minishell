/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exchain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:45:35 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:45:36 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCHAIN_H
# define EXCHAIN_H

typedef struct s_ex_chain
{
	int				exit_code;
	pid_t			pid;
	unsigned long	i;
	int				fd;
	t_raw_command	*raw;
	t_command		cmd;
	int				ports[2];
}	t_exchain;

#endif