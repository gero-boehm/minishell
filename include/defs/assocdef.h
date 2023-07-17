/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assocdef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:31:18 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/07 16:32:56 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSOCDEF_H
# define ASSOCDEF_H

# include "arraydef.h"

typedef struct s_assoc {
	t_array	keys;
	t_array	values;
}	t_assoc;

#endif