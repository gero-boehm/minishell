#ifndef CMDDEF_H
# define CMDDEF_H

# include "arraydef.h"
# include "rangedef.h"

typedef enum e_factory {
	// TODO: remove this and everything related to sequence factories
	F_SINGLE_CHAIN_SINGLE_BUILTIN,
	F_SINGLE_CHAIN_SINGLE_EXTERNAL,
	F_SINGLE_CHAIN_MULTIPLE_EXTERNAL,
	F_SINGLE_CHAIN_MULTIPLE_EXTERNAL_AND_BUILTINS,
	F_SINGLE_CHAIN_SINGLE_EXTERNAL_WITH_HEREDOC,
	F_MULTIPLE_CHAINS_SINGLE_EXTERNAL,
	F_MULTIPLE_CHAINS_SINGLE_EXTERNAL_AND_BUILTINS,
	F_MULTIPLE_CHAINS_MULTIPLE_EXTERNAL_AND_BUILTINS,
	F_MULTIPLE_CHAINS_ALL_BUILTINS
}	t_factory;

typedef enum e_op {
	OP_AND,
	OP_OR,
	OP_END
}	t_op;

typedef enum e_command_type {
	COMMAND_BUILTIN_ECHO,
	COMMAND_BUILTIN_CD,
	COMMAND_BUILTIN_PWD,
	COMMAND_BUILTIN_EXPORT,
	COMMAND_BUILTIN_UNSET,
	COMMAND_BUILTIN_ENV,
	COMMAND_BUILTIN_EXIT,
	COMMAND_EXTERNAL
}	t_command_type;

typedef enum e_file_type {
	FILE_IN,
	FILE_OUT,
	FILE_HEREDOC,
	FILE_APPEND,
}	t_file_type;

typedef struct s_heredoc {
	char	*str;
	t_array	vars;
}	t_heredoc;

typedef struct s_builtin_echo {
	char	*str;
	int		newline;
}	t_builtin_echo;

typedef struct s_builtin_cd {
	char	*path;
}	t_builtin_cd;

typedef struct s_builtin_export {
	char	**keys;
	char	**values;
}	t_builtin_export;

typedef struct s_builtin_unset {
	char	**keys;
}	t_builtin_unset;

typedef struct s_builtin_exit {
	char	*arg;
	int		too_many_args;
}	t_builtin_exit;

typedef struct s_external {
	char		**args;
}	t_external;

typedef union u_command_data {
	t_builtin_echo		builtin_echo;
	t_builtin_cd		builtin_cd;
	t_builtin_export	builtin_export;
	t_builtin_unset		builtin_unset;
	t_builtin_exit		builtin_exit;
	t_external			external;
}	t_command_data;

typedef struct s_command {
	int				fd_in;
	int				fd_out;
	t_command_type	type;
	t_command_data	data;
}	t_command;

typedef union u_file_data {
	t_heredoc	heredoc;
	char		*path;
}	t_file_data;

typedef struct s_file {
	t_file_type	type;
	t_file_data	data;
}	t_file;

typedef struct s_raw_command {
	t_array	args;
	t_array	files;
	t_array	vars_args;
	t_array	vars_files;
}	t_raw_command;

typedef struct s_chain {
	t_array		commands;
	t_op		op;
}	t_chain;

#endif