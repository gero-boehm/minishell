/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraydef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:33:08 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/16 18:05:48 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYDEF_H
# define ARRAYDEF_H

# include <stddef.h>

typedef struct s_array {
	void			*elements;
	size_t			size;
	size_t			max_size;
	unsigned int	bytes;
}	t_array;

#endif