/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assocdef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:45:22 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:45:24 by cmeng            ###   ########.fr       */
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