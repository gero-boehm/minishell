#ifndef ARRAY_H
# define ARRAY_H

# include <stddef.h>
# include "arraydef.h"

int		arr_create(t_array *arr, unsigned int bytes);
int		arr_add(t_array *arr, void *element);
int		arr_insert_at(t_array *arr, unsigned int index, void *element);
void	*arr_get(t_array *arr, unsigned int index);
void	arr_set(t_array *arr, unsigned int index, void *element);
int		arr_index(t_array *arr, void *element, unsigned int *index);
int		arr_remove(t_array *arr, void *element);
int		arr_remove_at(t_array *arr, unsigned int index);
void	arr_free(t_array *arr);

size_t	arr_size(t_array *arr);

int		arr_sort(t_array *arr, int (fn)(void *, void *));

void	arr_print_str(t_array *arr);

#endif