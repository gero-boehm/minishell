/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:35:57 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/24 19:40:46 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEQUENCE_H
# define SEQUENCE_H

#include "cmddef.h"
#include "arraydef.h"

int		sequence_factory(t_factory factory, t_array *sequence);
void	sequence_print(t_array *sequence);

#endif