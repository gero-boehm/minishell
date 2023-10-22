/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:47:45 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:47:45 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include "arraydef.h"

int	vars_extract(char *str,
		unsigned long index, unsigned long offset, t_array *vars);

int	vars_expand_str(t_array *vars, unsigned long index, char **str);
int	vars_expand_str_split(
		char *str, t_array *vars, unsigned long index, t_array *parts);

#endif