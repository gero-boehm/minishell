/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globaldef.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:45:40 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:45:41 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALDEF_H
# define GLOBALDEF_H

# include "arraydef.h"
# include "assocdef.h"

typedef struct s_global {
	char	*exec_path;
	int		exit_code;
	t_array	fds;
	t_assoc	env;
	t_array	allocs;
}	t_global;

#endif