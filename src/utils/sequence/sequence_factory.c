/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_factory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:04:06 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/01 13:20:34 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "memory.h"

void	copy_args(char **dst, char **src)
{
	while(*src != NULL)
		*dst++ = *src++;
}

int	single_chain_single_builtin(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ECHO;
	command00.data.builtin_echo.str = (char *) "ECHO_TEST";
	command00.data.builtin_echo.newline = 1;
	if (arr_add(&chain0, &command00))
		return (3);

	if (arr_add(sequence, &chain0))
		return (4);
}


int	single_chain_single_external(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	command00.data.external.cmd = (char *) "ls";
	char	*args00[] = {"ls", "-la", NULL};
	if (mem_alloc_str_arr(2, &command00.data.external.args))
		return (3);
	copy_args(command00.data.external.args, args00);
	command00.data.external.fd_in = 0;
	command00.data.external.fd_out = 1;
	command00.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command00))
		return (4);

	if (arr_add(sequence, &chain0))
		return (5);
}

int	single_chain_multiple_external(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	command00.data.external.cmd = (char *) "find";
	char	*args00[] = {"find", ".", "-type", "f", "-name", "*.c", NULL};
	if (mem_alloc_str_arr(6, &command00.data.external.args))
		return (3);
	copy_args(command00.data.external.args, args00);
	command00.data.external.fd_in = 0;
	command00.data.external.fd_out = 1;
	command00.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command00))
		return (4);

	t_command command01;
	command01.type = COMMAND_EXTERNAL;
	command01.data.external.cmd = (char *) "grep";
	char	*args01[] = {"grep", "utils", NULL};
	if (mem_alloc_str_arr(2, &command01.data.external.args))
		return (5);
	copy_args(command01.data.external.args, args01);
	command01.data.external.fd_in = 0;
	command01.data.external.fd_out = 1;
	command01.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command01))
		return (6);

	t_command command02;
	command02.type = COMMAND_EXTERNAL;
	command02.data.external.cmd = (char *) "wc";
	char	*args02[] = {"wc", "-l", NULL};
	if (mem_alloc_str_arr(2, &command02.data.external.args))
		return (7);
	copy_args(command02.data.external.args, args02);
	command02.data.external.fd_in = 0;
	command02.data.external.fd_out = 1;
	command02.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command02))
		return (8);

	if (arr_add(sequence, &chain0))
		return (9);
}

int	single_chain_multiple_external_and_builtins(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ENV;
	if (arr_add(&chain0, &command00))
		return (4);

	t_command command01;
	command01.type = COMMAND_EXTERNAL;
	command01.data.external.cmd = (char *) "grep";
	char	*args01[] = {"grep", "PATH", NULL};
	if (mem_alloc_str_arr(2, &command01.data.external.args))
		return (5);
	copy_args(command01.data.external.args, args01);
	command01.data.external.fd_in = 0;
	command01.data.external.fd_out = 1;
	command01.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command01))
		return (6);

	t_command command02;
	command02.type = COMMAND_EXTERNAL;
	command02.data.external.cmd = (char *) "tr";
	char	*args02[] = {"tr", ":", "\n", NULL};
	if (mem_alloc_str_arr(3, &command02.data.external.args))
		return (7);
	copy_args(command02.data.external.args, args02);
	command02.data.external.fd_in = 0;
	command02.data.external.fd_out = 1;
	command02.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command02))
		return (8);

	if (arr_add(sequence, &chain0))
		return (9);
}

int	single_chain_single_external_with_heredoc(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	command00.data.external.cmd = (char *) "ls";
	char	*args0[] = {"ls", "-la", NULL};
	if (mem_alloc_str_arr(2, &command00.data.external.args))
		return (3);
	copy_args(command00.data.external.args, args0);
	command00.data.external.fd_in = 0;
	command00.data.external.fd_out = 1;
	command00.data.external.heredoc.available = 1;
	command00.data.external.heredoc.available = 1;
	command00.data.external.heredoc.expand = 1;
	command00.data.external.heredoc.str = (char *) "this is a $TEST.";
	if (arr_create(&command00.data.external.heredoc.vars, sizeof(t_heredoc_var)))
		return (4);

	t_heredoc_var var;
	var.key = (char *) "TEST";
	var.range.start = 10;
	var.range.length = 5;

	if (arr_add(&command00.data.external.heredoc.vars, &var))
		return (5);

	if (arr_add(&chain0, &command00))
		return (6);

	if (arr_add(sequence, &chain0))
		return (7);
}

int	multiple_chains_single_external(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_AND;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	command00.data.external.cmd = (char *) "cal";
	char	*args00[] = {"cal", NULL};
	if (mem_alloc_str_arr(1, &command00.data.external.args))
		return (3);
	copy_args(command00.data.external.args, args00);
	command00.data.external.fd_in = 0;
	command00.data.external.fd_out = 1;
	command00.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command00))
		return (4);

	if (arr_add(sequence, &chain0))
		return (5);

	t_chain chain1;
	chain1.op = OP_AND;
	if (arr_create(&chain1.commands, sizeof(t_command)))
		return (6);

	t_command command10;
	command10.type = COMMAND_EXTERNAL;
	command10.data.external.cmd = (char *) "date";
	char	*args10[] = {"date", NULL};
	if (mem_alloc_str_arr(1, &command10.data.external.args))
		return (7);
	copy_args(command10.data.external.args, args10);
	command10.data.external.fd_in = 0;
	command10.data.external.fd_out = 1;
	command10.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command10))
		return (8);

	if (arr_add(sequence, &chain1))
		return (9);

	t_chain chain2;
	chain2.op = OP_END;
	if (arr_create(&chain2.commands, sizeof(t_command)))
		return (10);

	t_command command20;
	command20.type = COMMAND_EXTERNAL;
	command20.data.external.cmd = (char *) "uptime";
	char	*args20[] = {"uptime", NULL};
	if (mem_alloc_str_arr(1, &command20.data.external.args))
		return (11);
	copy_args(command20.data.external.args, args20);
	command20.data.external.fd_in = 0;
	command20.data.external.fd_out = 1;
	command20.data.external.heredoc.available = 0;
	if (arr_add(&chain2, &command20))
		return (12);

	if (arr_add(sequence, &chain2))
		return (13);
}

int	multiple_chains_single_external_and_builtins(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_AND;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ECHO;
	command00.data.builtin_echo.str = "echo echo echo";
	command00.data.builtin_echo.newline = 1;
	if (arr_add(&chain0, &command00))
		return (3);

	if (arr_add(sequence, &chain0))
		return (4);

	t_chain chain1;
	chain1.op = OP_AND;
	if (arr_create(&chain1.commands, sizeof(t_command)))
		return (5);

	t_command command10;
	command10.type = COMMAND_EXTERNAL;
	command10.data.external.cmd = (char *) "ps";
	char	*args10[] = {"ps", NULL};
	if (mem_alloc_str_arr(1, &command10.data.external.args))
		return (6);
	copy_args(command10.data.external.args, args10);
	command10.data.external.fd_in = 0;
	command10.data.external.fd_out = 1;
	command10.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command10))
		return (7);

	if (arr_add(sequence, &chain1))
		return (8);
}

int	multiple_chains_multiple_external_and_builtins(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_AND;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ECHO;
	command00.data.builtin_echo.str = "this is a string with spaces";
	command00.data.builtin_echo.newline = 1;
	if (arr_add(&chain0, &command00))
		return (3);

	t_command command01;
	command01.type = COMMAND_EXTERNAL;
	command01.data.external.cmd = (char *) "tr";
	char	*args01[] = {"tr", " ", "_", NULL};
	if (mem_alloc_str_arr(3, &command01.data.external.args))
		return (6);
	copy_args(command01.data.external.args, args01);
	command01.data.external.fd_in = 0;
	command01.data.external.fd_out = 1;
	command01.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command01))
		return (7);

	if (arr_add(sequence, &chain0))
		return (5);

	t_chain chain1;
	chain1.op = OP_AND;
	if (arr_create(&chain1.commands, sizeof(t_command)))
		return (6);

	t_command command10;
	command10.type = COMMAND_EXTERNAL;
	command10.data.external.cmd = (char *) "du";
	char	*args10[] = {"du", "-h", NULL};
	if (mem_alloc_str_arr(2, &command10.data.external.args))
		return (7);
	copy_args(command10.data.external.args, args10);
	command10.data.external.fd_in = 0;
	command10.data.external.fd_out = 1;
	command10.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command10))
		return (8);

	t_command command11;
	command11.type = COMMAND_EXTERNAL;
	command11.data.external.cmd = (char *) "sort";
	char	*args11[] = {"sort", "-rh", NULL};
	if (mem_alloc_str_arr(2, &command11.data.external.args))
		return (7);
	copy_args(command11.data.external.args, args11);
	command11.data.external.fd_in = 0;
	command11.data.external.fd_out = 1;
	command11.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command11))
		return (8);

	t_command command12;
	command12.type = COMMAND_EXTERNAL;
	command12.data.external.cmd = (char *) "head";
	char	*args12[] = {"head", "-n", "1", NULL};
	if (mem_alloc_str_arr(3, &command12.data.external.args))
		return (7);
	copy_args(command12.data.external.args, args12);
	command12.data.external.fd_in = 0;
	command12.data.external.fd_out = 1;
	command12.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command12))
		return (8);

	if (arr_add(sequence, &chain1))
		return (9);

	t_chain chain2;
	chain2.op = OP_END;
	if (arr_create(&chain2.commands, sizeof(t_command)))
		return (10);

	t_command command20;
	command20.type = COMMAND_EXTERNAL;
	command20.data.external.cmd = (char *) "cat";
	char	*args20[] = {"cat", "/dev/urandom", NULL};
	if (mem_alloc_str_arr(2, &command20.data.external.args))
		return (11);
	copy_args(command20.data.external.args, args20);
	command20.data.external.fd_in = 0;
	command20.data.external.fd_out = 1;
	command20.data.external.heredoc.available = 0;
	if (arr_add(&chain2, &command20))
		return (12);

	t_command command21;
	command21.type = COMMAND_EXTERNAL;
	command21.data.external.cmd = (char *) "head";
	char	*args21[] = {"head", "-5", NULL};
	if (mem_alloc_str_arr(2, &command21.data.external.args))
		return (11);
	copy_args(command21.data.external.args, args21);
	command21.data.external.fd_in = 0;
	command21.data.external.fd_out = 1;
	command21.data.external.heredoc.available = 0;
	if (arr_add(&chain2, &command21))
		return (12);

	if (arr_add(sequence, &chain2))
		return (13);
}

int	sequence_factory(t_factory factory, t_array *sequence)
{
	if (factory == F_SINGLE_CHAIN_SINGLE_BUILTIN)
		return single_chain_single_builtin(sequence);
	if (factory == F_SINGLE_CHAIN_SINGLE_EXTERNAL)
		return single_chain_single_external(sequence);
	if (factory == F_SINGLE_CHAIN_MULTIPLE_EXTERNAL)
		return single_chain_multiple_external(sequence);
	if (factory == F_SINGLE_CHAIN_MULTIPLE_EXTERNAL_AND_BUILTINS)
		return single_chain_multiple_external_and_builtins(sequence);
	if (factory == F_SINGLE_CHAIN_SINGLE_EXTERNAL_WITH_HEREDOC)
		return single_chain_single_external_with_heredoc(sequence);
	if (factory == F_MULTIPLE_CHAINS_SINGLE_EXTERNAL)
		return multiple_chains_single_external(sequence);
	if (factory == F_MULTIPLE_CHAINS_SINGLE_EXTERNAL_AND_BUILTINS)
		return multiple_chains_single_external_and_builtins(sequence);
	if (factory == F_MULTIPLE_CHAINS_MULTIPLE_EXTERNAL_AND_BUILTINS)
		return multiple_chains_multiple_external_and_builtins(sequence);
}

