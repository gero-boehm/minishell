/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:38:55 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 15:00:27 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "memory.h"

static void	trim(char **str, char c)
{
	while (**str == c)
		(*str)++;
}

static int	grab_word(char **str, char c, t_array *arr)
{
	size_t	len;
	char	*word;

	len = 0;
	while ((*str)[len] && (*str)[len] != c)
		len++;
	if (mem_alloc_str(len, &word))
		return (1);
	mem_ncpy(word, *str, len);
	if (arr_add(arr, &word))
		return (2);
	*str += len;
	return (0);
}

int	str_split(char *str, char c, t_array *arr)
{
	if (arr_create(arr, sizeof(char *)))
		return (1);
	while (*str)
	{
		trim(&str, c);
		if (*str == 0)
			return (0);
		if (grab_word(&str, c, arr))
			return (2);
	}
	return (0);
}
