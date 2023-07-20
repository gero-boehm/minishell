/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmddef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:44:17 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 14:47:18 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDDEF_H
# define CMDDEF_H

enum e_op {
	AND,
	OR,
	END
};

typedef struct s_command {
	char	*cmd;
	char	**args;
	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_sequence {
	t_command	cmd;
	e_op		op;
}	t_sequence;

#endif