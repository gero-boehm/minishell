/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:48:48 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:48:49 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "globaldef.h"

t_global	*global(void);
char		*shell_name(void);
int			global_init(char *exec_name);
void		cleanup(void);

#endif