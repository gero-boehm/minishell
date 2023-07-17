/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:18:10 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 14:21:50 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*str_cpy(char *dst, const char *src)
{
	char	*cursor;

	cursor = dst;
	while (*src != '\0')
		*cursor++ = *src++;
	return (dst);
}

size_t	str_cpyn(char *dst, const char *src)
{
	str_cpy(dst, src);
	return (str_len(src));
}
