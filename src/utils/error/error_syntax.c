/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:54:08 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:54:08 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int	return_syntax(char *token)
{
	return (str_print_error(258,
			"syntax error near unexpected token `", token, "'", NULL));
}
