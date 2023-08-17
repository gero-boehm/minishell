/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globaldef.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:33:08 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/07 14:26:09 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALDEF_H
# define GLOBALDEF_H

# include "arraydef.h"
# include "assocdef.h"

typedef struct s_global {
	t_array	fds;
	t_assoc	env;
	t_array	allocs;
	t_array	heredocs;
}	t_global;

int	g_signal;

#endif