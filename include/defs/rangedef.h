/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rangedef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:45:51 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:45:52 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANGEDEF_H
# define RANGEDEF_H

# include <stddef.h>
# include "lexerdef.h"
# include "arraydef.h"

typedef struct s_var_data {
	unsigned long	index;
	char			*key;
}	t_var_data;

typedef union u_range_meta {
	t_quote			quote;
	t_var_data		var_data;
}	t_range_meta;

typedef struct s_range {
	unsigned long	start;
	size_t			length;
	t_range_meta	meta;
}	t_range;

#endif