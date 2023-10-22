/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:03 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:03 by cmeng            ###   ########.fr       */
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
	if (src == NULL)
		return (0);
	str_cpy(dst, src);
	return (str_len(src));
}
