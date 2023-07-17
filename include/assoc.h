/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:49:33 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:37:11 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSOC_H
# define ASSOC_H

# include <stddef.h>
# include "assocdef.h"

int		assoc_create(t_assoc *assoc);
int		assoc_set(t_assoc *assoc, const char *key, char *value);
int		assoc_get(t_assoc *assoc, const char *key, char **value);
char	*assoc_get_key_at(t_assoc *assoc, unsigned int index);
char	*assoc_get_value_at(t_assoc *assoc, unsigned int index);
int		assoc_remove(t_assoc *assoc, const char *key);
size_t	assoc_size(t_assoc *assoc);
int		assoc_from_str_arr(t_assoc *assoc, char **arr);
int		assoc_to_str_arr(t_assoc *assoc, char ***arr);

void	assoc_print(t_assoc *assoc);

#endif