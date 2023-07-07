/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:32:49 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/07 14:16:00 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include "stddef.h"

typedef struct s_array {
	void			*elements;
	size_t			size;
	size_t			max_size;
	unsigned int	bytes;
}	t_array;

typedef struct s_global {
	// t_vars	vars;
	t_array	allocs;
}	t_global;

typedef struct s_range {
	unsigned long	start;
	size_t			length;
}	t_range;

t_global g_global;

int		memalloc(size_t count, void **ptr);
int		memfree(void *ptr);

int		arr_create(t_array *arr, unsigned int bytes);
int		arr_add(t_array *arr, void *element);
void	*arr_get(t_array *arr, unsigned int index);
void	arr_set(t_array *arr, unsigned int index, void *element);
int		arr_index(t_array *arr, void *element, unsigned int *index);
int		arr_remove(t_array *arr, void *element);
int		arr_remove_at(t_array *arr, unsigned int index);
void	arr_free(t_array *arr);

void	arr_print_ptr(t_array *arr);

// int		vars_init(void);
// int		var_set(char *key, char *value);
// int		var_get(char *key, char **value);
// void	vars_print(void);



#endif