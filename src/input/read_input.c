/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:50:59 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:51:00 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "array.h"
#include "memory.h"
#include "str.h"
#include "error.h"
#include "minishell.h"

static void	read_loop(int *bytes_read, char *letter, t_array *letters)
{
	while (1)
	{
		*bytes_read = read(STDIN_FILENO, letter, 1);
		if (*bytes_read < 0)
			error_fatal();
		if (*bytes_read == 0 || *letter == '\n')
			break ;
		if (arr_add(letters, letter))
			error_fatal();
	}
}

int	read_input(char **str)
{
	unsigned long	i;
	t_array			letters;
	char			letter;
	int				bytes_read;

	if (arr_create(&letters, sizeof(char)))
		error_fatal();
	read_loop(&bytes_read, &letter, &letters);
	if (mem_alloc_str(arr_size(&letters), str))
		error_fatal();
	i = 0;
	while (i < arr_size(&letters))
	{
		(*str)[i] = *(char *) arr_get(&letters, i);
		i++;
	}
	arr_free(&letters);
	return (str_len(*str) == 0 && bytes_read == 0);
}
