/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:45:09 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/03 18:45:37 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraydef.h"

#ifndef VARS_H
# define VARS_H

int	vars_expand_str(t_array *vars, char **str);
int	vars_expand_str_arr(t_array *vars, char **str);

#endif