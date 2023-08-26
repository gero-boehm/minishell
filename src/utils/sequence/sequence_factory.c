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
	command00.fd_in = 0;
	command00.fd_out = 1;
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
		return (1);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	char	*args00[] = {"ls", "-la", NULL};
	// command00.data.external.args = args00;
	// command00.data.external.cmd = (char *) "ls";
	// char	*args00[] = {"ls", "-la", NULL};
	if (mem_alloc_str_arr(2, &command00.data.external.args))
		return (1);
	copy_args(command00.data.external.args, args00);
	command00.fd_in = 0;
	command00.fd_out = 1;
	// command00.heredoc.available = 0;
	if (arr_add(&chain0, &command00))
		return (4);

	if (arr_add(sequence, &chain0))
		return (1);

	return (0);
}

int	single_chain_multiple_external(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (1);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	char	*args00[] = {"find", ".", "-type", "f", "-name", "*.c", NULL};
	if (mem_alloc_str_arr(6, &command00.data.external.args))
		return (1);
	copy_args(command00.data.external.args, args00);

	command00.fd_in = 0;
	command00.fd_out = 1;
	// command00.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command00))
		return (4);

	t_command command01;
	command01.type = COMMAND_EXTERNAL;
	// command01.data.external.cmd = (char *) "grep";
	char	*args01[] = {"grep", "utils", NULL};
	if (mem_alloc_str_arr(2, &command01.data.external.args))
		return (1);
	copy_args(command01.data.external.args, args01);
	command01.fd_in = 0;
	command01.fd_out = 1;
	// command01.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command01))
		return (6);

	t_command command02;
	command02.type = COMMAND_EXTERNAL;
	// command02.data.external.cmd = (char *) "wc";
	char	*args02[] = {"wc", "-l", NULL};
	if (mem_alloc_str_arr(2, &command02.data.external.args))
		return (1);
	copy_args(command02.data.external.args, args02);
	command02.fd_in = 0;
	command02.fd_out = 1;
	// command02.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command02))
		return (8);

	if (arr_add(sequence, &chain0))
		return (1);

	return (0);
}

int	single_chain_multiple_external_and_builtins(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (1);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ENV;
	command00.fd_in = 0;
	command00.fd_out = 1;
	if (arr_add(&chain0.commands, &command00))
		return (1);

	t_command command01;
	command01.type = COMMAND_EXTERNAL;
	char	*args01[] = {"grep", "PATH", NULL};
	if (mem_alloc_str_arr(2, &command01.data.external.args))
		return (1);
	copy_args(command01.data.external.args, args01);
	command01.fd_in = 0;
	command01.fd_out = 1;
	// command01.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command01))
		return (6);

	t_command command02;
	command02.type = COMMAND_EXTERNAL;
	// command02.data.external.cmd = (char *) "tr";
	char	*args02[] = {"tr", ":", "\n", NULL};
	if (mem_alloc_str_arr(3, &command02.data.external.args))
		return (1);
	copy_args(command02.data.external.args, args02);
	command02.fd_in = 0;
	command02.fd_out = 1;
	// command02.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command02))
		return (8);

	if (arr_add(sequence, &chain0))
		return (1);

	return (0);
}

int	multiple_chains_single_external(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_AND;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (1);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	char	*args00[] = {"cal", NULL};
	if (mem_alloc_str_arr(1, &command00.data.external.args))
		return (1);
	copy_args(command00.data.external.args, args00);
	command00.fd_in = 0;
	command00.fd_out = 1;
	// command00.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command00))
		return (4);

	if (arr_add(sequence, &chain0))
		return (1);

	t_chain chain1;
	chain1.op = OP_AND;
	if (arr_create(&chain1.commands, sizeof(t_command)))
		return (1);

	t_command command10;
	command10.type = COMMAND_EXTERNAL;
	char	*args10[] = {"date", NULL};
	if (mem_alloc_str_arr(1, &command10.data.external.args))
		return (1);
	copy_args(command10.data.external.args, args10);
	command10.fd_in = 0;
	command10.fd_out = 1;
	// command10.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command10))
		return (8);

	if (arr_add(sequence, &chain1))
		return (1);

	t_chain chain2;
	chain2.op = OP_END;
	if (arr_create(&chain2.commands, sizeof(t_command)))
		return (10);

	t_command command20;
	command20.type = COMMAND_EXTERNAL;
	char	*args20[] = {"uptime", NULL};
	if (mem_alloc_str_arr(1, &command20.data.external.args))
		return (1);
	copy_args(command20.data.external.args, args20);
	command20.fd_in = 0;
	command20.fd_out = 1;
	// command20.data.external.heredoc.available = 0;
	if (arr_add(&chain2, &command20))
		return (12);

	if (arr_add(sequence, &chain2))
		return (1);

	return (0);
}

int	multiple_chains_single_external_and_builtins(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_AND;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (1);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ECHO;
	command00.data.builtin_echo.str = "echo echo echo";
	command00.data.builtin_echo.newline = 1;
	command00.fd_in = 0;
	command00.fd_out = 1;
	if (arr_add(&chain0.commands, &command00))
		return (1);

	if (arr_add(sequence, &chain0))
		return (1);

	t_chain chain1;
	chain1.op = OP_AND;
	if (arr_create(&chain1.commands, sizeof(t_command)))
		return (1);

	t_command command10;
	command10.type = COMMAND_EXTERNAL;
	char	*args10[] = {"ps", NULL};
	if (mem_alloc_str_arr(1, &command10.data.external.args))
		return (1);
	copy_args(command10.data.external.args, args10);
	command10.fd_in = 0;
	command10.fd_out = 1;
	// command10.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command10))
		return (7);

	if (arr_add(sequence, &chain1))
		return (1);

	return (0);
}

int	multiple_chains_multiple_external_and_builtins(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_AND;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (1);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ECHO;
	command00.data.builtin_echo.str = "this is a string with spaces";
	command00.data.builtin_echo.newline = 1;
	command00.fd_in = 0;
	command00.fd_out = 1;
	if (arr_add(&chain0.commands, &command00))
		return (1);

	t_command command01;
	command01.type = COMMAND_EXTERNAL;
	char	*args01[] = {"tr", " ", "_", NULL};
	if (mem_alloc_str_arr(3, &command01.data.external.args))
		return (1);
	copy_args(command01.data.external.args, args01);
	command01.fd_in = 0;
	command01.fd_out = 1;
	// command01.data.external.heredoc.available = 0;
	if (arr_add(&chain0, &command01))
		return (7);

	if (arr_add(sequence, &chain0))
		return (1);

	t_chain chain1;
	chain1.op = OP_AND;
	if (arr_create(&chain1.commands, sizeof(t_command)))
		return (1);

	t_command command10;
	command10.type = COMMAND_EXTERNAL;
	char	*args10[] = {"du", "-h", NULL};
	if (mem_alloc_str_arr(2, &command10.data.external.args))
		return (1);
	copy_args(command10.data.external.args, args10);
	command10.fd_in = 0;
	command10.fd_out = 1;
	// command10.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command10))
		return (8);

	t_command command11;
	command11.type = COMMAND_EXTERNAL;
	// command11.data.external.cmd = (char *) "sort";
	char	*args11[] = {"sort", "-rh", NULL};
	if (mem_alloc_str_arr(2, &command11.data.external.args))
		return (1);
	copy_args(command11.data.external.args, args11);
	command11.fd_in = 0;
	command11.fd_out = 1;
	// command11.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command11))
		return (8);

	t_command command12;
	command12.type = COMMAND_EXTERNAL;
	// command12.data.external.cmd = (char *) "head";
	char	*args12[] = {"head", "-n", "1", NULL};
	if (mem_alloc_str_arr(3, &command12.data.external.args))
		return (1);
	copy_args(command12.data.external.args, args12);
	command12.fd_in = 0;
	command12.fd_out = 1;
	// command12.data.external.heredoc.available = 0;
	if (arr_add(&chain1, &command12))
		return (8);

	if (arr_add(sequence, &chain1))
		return (1);

	t_chain chain2;
	chain2.op = OP_END;
	if (arr_create(&chain2.commands, sizeof(t_command)))
		return (10);

	t_command command20;
	command20.type = COMMAND_EXTERNAL;
	char	*args20[] = {"cat", "/dev/urandom", NULL};
	if (mem_alloc_str_arr(2, &command20.data.external.args))
		return (1);
	copy_args(command20.data.external.args, args20);
	command20.fd_in = 0;
	command20.fd_out = 1;
	// command20.data.external.heredoc.available = 0;
	if (arr_add(&chain2, &command20))
		return (12);

	t_command command21;
	command21.type = COMMAND_EXTERNAL;
	// command21.data.external.cmd = (char *) "head";
	char	*args21[] = {"head", "-5", NULL};
	if (mem_alloc_str_arr(2, &command21.data.external.args))
		return (1);
	copy_args(command21.data.external.args, args21);
	command21.fd_in = 0;
	command21.fd_out = 1;
	// command21.data.external.heredoc.available = 0;
	if (arr_add(&chain2, &command21))
		return (12);

	if (arr_add(sequence, &chain2))
		return (1);

	return (0);
}

int	multiple_chains_all_builtins(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_AND;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (1);

	t_command command00;
	command00.type = COMMAND_BUILTIN_ECHO;
	command00.data.builtin_echo.str = "just a regular string";
	command00.data.builtin_echo.newline = 1;
	command00.fd_in = 0;
	command00.fd_out = 1;

	if (arr_add(&chain0.commands, &command00))
		return (1);

	if (arr_add(sequence, &chain0))
		return (1);

	t_chain chain1;
	chain1.op = OP_AND;

	if (arr_create(&chain1.commands, sizeof(t_command)))
		return (1);

	t_command command10;
	command10.type = COMMAND_BUILTIN_PWD;
	command10.fd_in = 0;
	command10.fd_out = 1;
	if (arr_add(&chain1.commands, &command10))
		return (1);

	if (arr_add(sequence, &chain1))
		return (1);


	t_chain chain2;
	chain2.op = OP_AND;
	if (arr_create(&chain2.commands, sizeof(t_command)))
		return (1);

	t_command command20;
	command20.type = COMMAND_BUILTIN_ENV;
	command20.fd_in = 0;
	command20.fd_out = 1;
	if (arr_add(&chain2.commands, &command20))
		return (1);

	if (arr_add(sequence, &chain2))
		return (1);


	t_chain chain3;
	chain3.op = OP_AND;
	if (arr_create(&chain3.commands, sizeof(t_command)))
		return (1);

	t_command command30;
	command30.type = COMMAND_BUILTIN_CD;
	command30.data.builtin_cd.path = "-";
	command30.fd_in = 0;
	command30.fd_out = 1;
	if (arr_add(&chain3.commands, &command30))
		return (1);

	if (arr_add(sequence, &chain3))
		return (1);


	t_chain chain4;
	chain4.op = OP_AND;
	if (arr_create(&chain4.commands, sizeof(t_command)))
		return (1);

	t_command command40;
	command40.type = COMMAND_BUILTIN_EXPORT;
	if (mem_alloc_str_arr(2, &command40.data.builtin_export.keys))
		return (1);
	if (mem_alloc_str_arr(2, &command40.data.builtin_export.values))
		return (1);
	char	*args40k[] = {"A", "B", NULL};
	char	*args40v[] = {"hello", "world", NULL};
	copy_args(command40.data.builtin_export.keys, args40k);
	copy_args(command40.data.builtin_export.values, args40v);
	command40.fd_in = 0;
	command40.fd_out = 1;
	if (arr_add(&chain4.commands, &command40))
		return (1);

	if (arr_add(sequence, &chain4))
		return (1);

	t_chain chain5;
	chain5.op = OP_AND;
	if (arr_create(&chain5.commands, sizeof(t_command)))
		return (1);

	t_command command50;
	command50.type = COMMAND_BUILTIN_ENV;
	command50.fd_in = 0;
	command50.fd_out = 1;
	if (arr_add(&chain5.commands, &command50))
		return (1);

	if (arr_add(sequence, &chain5))
		return (1);

	t_chain chain6;
	chain6.op = OP_AND;
	if (arr_create(&chain6.commands, sizeof(t_command)))
		return (1);

	t_command command60;
	command60.type = COMMAND_BUILTIN_UNSET;
	if (mem_alloc_str_arr(2, &command60.data.builtin_unset.keys))
		return (1);
	char	*args60k[] = {"A", "B", NULL};
	copy_args(command60.data.builtin_unset.keys, args60k);
	command60.fd_in = 0;
	command60.fd_out = 1;
	if (arr_add(&chain6.commands, &command60))
		return (1);

	if (arr_add(sequence, &chain6))
		return (1);


	t_chain chain7;
	chain7.op = OP_AND;
	if (arr_create(&chain7.commands, sizeof(t_command)))
		return (1);

	t_command command70;
	command70.type = COMMAND_BUILTIN_ENV;
	command70.fd_in = 0;
	command70.fd_out = 1;
	if (arr_add(&chain7.commands, &command70))
		return (1);

	if (arr_add(sequence, &chain7))
		return (1);

	t_chain chain8;
	chain8.op = OP_END;
	if (arr_create(&chain8.commands, sizeof(t_command)))
		return (8);

	t_command command80;
	command80.type = COMMAND_BUILTIN_EXIT;
	command80.data.builtin_exit.arg = "";
	command80.data.builtin_exit.too_many_args = 1;
	command80.fd_in = 0;
	command80.fd_out = 8;
	if (arr_add(&chain8.commands, &command80))
		return (8);

	if (arr_add(sequence, &chain8))
		return (1);

	return (0);

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
	if (factory == F_MULTIPLE_CHAINS_SINGLE_EXTERNAL)
		return multiple_chains_single_external(sequence);
	if (factory == F_MULTIPLE_CHAINS_SINGLE_EXTERNAL_AND_BUILTINS)
		return multiple_chains_single_external_and_builtins(sequence);
	if (factory == F_MULTIPLE_CHAINS_MULTIPLE_EXTERNAL_AND_BUILTINS)
		return multiple_chains_multiple_external_and_builtins(sequence);
	if (factory == F_MULTIPLE_CHAINS_ALL_BUILTINS)
		return multiple_chains_all_builtins(sequence);
	return (100);
}

