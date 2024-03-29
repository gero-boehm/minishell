/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assoc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:49:11 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:49:12 by cmeng            ###   ########.fr       */
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
int		assoc_index(t_assoc *assoc, const char *match, unsigned long *index);
int		assoc_from_str_arr(t_assoc *assoc, char **arr);
int		assoc_to_str_arr(t_assoc *assoc, char ***arr);

void	assoc_print(t_assoc *assoc);

#endif