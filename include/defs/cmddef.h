/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmddef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:44:17 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/25 00:35:18 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDDEF_H
# define CMDDEF_H

# include "arraydef.h"
# include "strdef.h"

typedef enum e_factory {
	F_SINGLE_LINK_SINGLE_EXTERNAL,
	F_SINGLE_LINK_MULTIPLE_EXTERNAL,
	F_SINGLE_LINK_MULTIPLE_EXTERNAL_AND_BUILTINS,
	F_SINGLE_LINK_SINGLE_EXTERNAL_WITH_HEREDOC,
	F_MULTIPLE_LINKS_SINGLE_EXTERNAL,
	F_MULTIPLE_LINKS_SINGLE_EXTERNAL_AND_BUILTINS,
	F_MULTIPLE_LINKS_MULTIPLE_EXTERNAL
}	t_factory;

typedef enum e_op {
	OP_AND,
	OP_OR,
	OP_END
}	t_op;

typedef enum e_command_type {
	COMMAND_BUILTIN_ECHO,
	COMMAND_BUILTIN_CD,
	COMMAND_BUILTIN_EXPORT,
	COMMAND_BUILTIN_UNSET,
	COMMAND_BUILTIN_ENV,
	COMMAND_BUILTIN_EXIT,
	COMMAND_EXTERNAL
}	t_command_type;

typedef struct s_heredoc_var {
	char	*key;
	t_range	range;
}	t_heredoc_var;

typedef struct s_heredoc {
	int		available;
	int		expand;
	char	*str;
	t_array	vars;
}	t_heredoc;

typedef struct s_builtin_echo {
	char	*str;
	int		flag;
}	t_builtin_echo;

typedef struct s_builtin_cd {
	char	*path;
}	t_builtin_cd;

typedef struct s_builtin_export {
	char	*key;
	char	*value;
}	t_builtin_export;

typedef struct s_builtin_unset {
	char	*key;
}	t_builtin_unset;

typedef struct s_external {
	char		*cmd;
	char		**args;
	int			fd_in;
	int			fd_out;
	t_heredoc	heredoc;
}	t_external;

typedef union u_command_data {
	t_builtin_echo		builtin_echo;
	t_builtin_cd		builtin_cd;
	t_builtin_export	builtin_export;
	t_builtin_unset		builtin_unset;
	t_external			external;
}	t_command_data;

typedef struct s_command {
	t_command_type	type;
	t_command_data	data;
}	t_command;

typedef struct s_chain {
	t_array		commands;
	t_op		op;
}	t_chain;

#endif