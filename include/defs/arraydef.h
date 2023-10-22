/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraydef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:45:14 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:45:16 by cmeng            ###   ########.fr       */
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