/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:35:35 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/11 14:03:46 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "arraydef.h"

int	get_paths(char *pattern, t_array *paths);


int	is_pattern_matching(char *name, char *pattern);


#endif