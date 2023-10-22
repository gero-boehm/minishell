/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:47:32 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:47:42 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include <stddef.h>
# include "arraydef.h"
# include "rangedef.h"

int		arr_create(t_array *arr, unsigned int bytes);
int		arr_clone(t_array *arr, t_array *clone);
int		arr_add(t_array *arr, void *element);
int		arr_insert_at(t_array *arr, unsigned long index, void *element);
int		arr_insert_arr(t_array *dst, unsigned long index, t_array *src);
void	*arr_get(t_array *arr, unsigned long index);
void	arr_set(t_array *arr, unsigned long index, void *element);
int		arr_index(t_array *arr, void *element, unsigned long *index);
int		arr_remove(t_array *arr, void *element);
int		arr_remove_at(t_array *arr, unsigned long index);
void	arr_free(t_array *arr);
void	arr_free_ptr(t_array *arr);

size_t	arr_size(t_array *arr);

int		arr_sort(t_array *arr, int (fn)(void *, void *));

int		arr_sub(t_array *arr, t_range *range, t_array *sub);
int		arr_sub_mask(t_array *arr, t_array *mask, t_array *sub);

void	arr_print_str(t_array *arr);
void	arr_print_ptr(t_array *arr);

#endif