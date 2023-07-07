/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:35:40 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/07 16:36:39 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRDEF_H
# define STRDEF_H

# include <stddef.h>

typedef struct s_range {
	unsigned long	start;
	size_t			length;
}	t_range;

#endif