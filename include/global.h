/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:23:16 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/06 15:05:15 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "globaldef.h"

t_global	*global(void);
int			global_init(void);
void		cleanup(void);
void		error(int code);
void		success(void);

#endif