/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:37:25 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:37:55 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assocdef.h"
#include "array.h"

int	assoc_create(t_assoc *assoc)
{
	if (arr_create(&assoc->keys, sizeof(char *)))
		return (1);
	if (arr_create(&assoc->values, sizeof(char *)))
		return (2);
	return (0);
}
