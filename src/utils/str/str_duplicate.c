/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_duplicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:16:06 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 15:00:27 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "memory.h"

int	str_dup(const char *str, char **dup)
{
	size_t	len;

	len = str_len(str);
	if (mem_alloc_str(len, dup))
		return (1);
	str_cpyn(*dup, str);
	return (0);
}