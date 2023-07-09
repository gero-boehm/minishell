/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:32:49 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/09 15:48:43 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include <stddef.h>
# include "arraydef.h"

int		arr_create(t_array *arr, unsigned int bytes);
int		arr_add(t_array *arr, void *element);
void	*arr_get(t_array *arr, unsigned int index);
void	arr_set(t_array *arr, unsigned int index, void *element);
int		arr_index(t_array *arr, void *element, unsigned int *index);
int		arr_remove(t_array *arr, void *element);
int		arr_remove_at(t_array *arr, unsigned int index);
void	arr_free(t_array *arr);

size_t	arr_size(t_array *arr);

int		arr_to_str_arr(t_array *arr, char ***strs);
int		arr_to_str(t_array *arr, char **str);


void	arr_print_str(t_array *arr);

#endif