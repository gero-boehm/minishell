/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_invalid_identifier.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:18 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:18 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int	return_invalid_identifier(const char *cmd, char *key, char *value)
{
	if (value == NULL)
		return (str_print_error(1, cmd, ": `", key,
				"': not a valid identifier", NULL));
	return (str_print_error(1, cmd, ": `", key, "=",
			value, "': not a valid identifier", NULL));
}
