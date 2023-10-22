/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:55:56 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:55:56 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "str.h"

int	append_str(const char *str, t_array *lines)
{
	char	*dup;

	if (str_dup(str, &dup))
		return (1);
	if (arr_add(lines, &dup))
		return (2);
	return (0);
}
