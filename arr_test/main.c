/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:55:21 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/04 18:06:17 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "array.h"

int	memalloc(size_t count, void **ptr)
{
	*ptr = malloc(count);
	if (*ptr == NULL)
		return (1);
	if (arr_add(&g_global.allocs, ptr))
		return (2);
	return (0);
}

int	memfree(void *ptr)
{
	if (arr_remove(&g_global.allocs, &ptr))
		return (1);
	free(ptr);
	return (0);
}

void	cleanup(void)
{
	unsigned int	i;
	void			*ptr;

	i = g_global.allocs.size;
	while(i--)
	{
		ptr = *(void **) arr_get(&g_global.allocs, i);
		free(ptr);
	}
}

int	init_global(void)
{
	if (arr_create(&g_global.allocs, sizeof(void *)))
		return (1);
	if (vars_init())
		return (2);
	return (0);
}

void	arr_print(t_array *arr)
{
	for (unsigned int i = 0; i < arr->size; i++)
	{
		int	element = *((int *) arr_get(arr, i));
		printf("%d ", element);
	}
	printf("\n");
}

void	arr_print_str(t_array *arr)
{
	for (unsigned int i = 0; i < arr->size; i++)
	{
		printf("%s\n", *(char **) arr_get(arr, i));
	}
}

void	arr_print_ptr(t_array *arr)
{
	for (unsigned int i = 0; i < arr->size; i++)
	{
		printf("%p ", *(void **) arr_get(arr, i));
	}
	printf("\n");
}

void	error(int code)
{
	cleanup();
	exit(code);
}

void	test_fancy(void)
{
	char *str;

	memalloc(6, (void **) &str);

	error(1);
}

void	test_normal(void)
{
	char *str = malloc(6);

	error(1);
}

int	main(int argc, char **argv, char** envp)
{
	t_array arr;

	init_global();
	// arr_print_ptr(&g_global.allocs);
	// arr_create(&arr, sizeof(int));
	// arr_print_ptr(&g_global.allocs);

	// var_set("test", "abc");
	// var_set("abc", "def");
	// arr_print_ptr(&g_global.allocs);
	// vars_print();
	// char *v;
	// var_get("test", &v);
	// printf("%s\n", v);

	t_array split;
	ft_split("  a b c def ", ' ', &split);

	arr_print_str(&split);

	// error(0);
	cleanup();
	return (0);
}