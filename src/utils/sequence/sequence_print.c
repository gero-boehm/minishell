/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:21:05 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/16 10:32:08 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cmddef.h"
#include "array.h"

#define RED				"\033[31m"
#define GREEN			"\033[32m"
#define YELLOW			"\033[33m"
#define CYAN			"\033[38;5;216m"
#define ORANGE			"\033[38;5;216m"
#define WHITE			"\033[37m"
#define PURPLE			"\033[38;2;81;97;205m"
#define TURQUOISE		"\033[38;2;71;176;157m"
#define GRAY			"\033[38;5;245m"
#define RESET			"\033[0m"

void	print_str_arr(char **arr)
{
	int	first = 1;

	printf("[");
	while (*arr != NULL)
	{
		if (!first)
			printf(", ");
		printf("%s'%s'%s", ORANGE, *arr, GRAY);
		first = 0;
		arr++;
	}
	printf("]\n");
}

void command_builtin_echo_print(t_builtin_echo *data_echo)
{
	printf(RESET WHITE "    echo " GRAY "{\n");
	printf("      str:     %s'%s'%s\n", ORANGE, data_echo->str, GRAY);
	printf("      newline: %s%s%s\n", data_echo->newline ? GREEN : RED, data_echo->newline ? "true" : "false", GRAY);
	print_vars(&data_echo->vars, "vars", 0, "    ");
	printf("    }\n");
}

void command_builtin_cd_print(t_builtin_cd *data_cd)
{
	printf(RESET WHITE "    cd " GRAY "{\n");
	printf("      path: %s'%s'%s\n", ORANGE, data_cd->path, GRAY);
	print_vars(&data_cd->vars, "vars", 0, " ");
	printf("    }\n");
}

void command_builtin_pwd_print(void)
{
	printf(RESET WHITE "    pwd " GRAY "{\n");
	printf("    }\n");
}

void command_builtin_export_print(t_builtin_export *data_export)
{
	printf(RESET WHITE "    export " GRAY "{\n");
	printf("      key:   %s'%s'%s\n", CYAN, *data_export->keys, GRAY);
	printf("      value: %s'%s'%s\n", CYAN, *data_export->keys, GRAY);
	printf("    }\n");
}

void command_builtin_unset_print(t_builtin_unset *data_unset)
{
	printf(RESET WHITE "    unset " GRAY "{\n");
	printf("      key: %s'%s'%s\n", CYAN, *data_unset->keys, GRAY);
	printf("    }\n");
}

void command_builtin_env_print(void)
{
	printf(RESET WHITE "    env " GRAY "{\n");
	printf("    }\n");
}

void command_builtin_exit_print(t_builtin_exit *data_exit)
{
	printf(RESET WHITE "    exit " GRAY "{\n");
	printf("      arg:           %s'%s'%s\n", ORANGE, data_exit->arg, GRAY);
	printf("      too_many_args: %s%s%s\n", data_exit->too_many_args ? GREEN : RED, data_exit->too_many_args ? "true" : "false", GRAY);
	print_vars(&data_exit->vars, "vars", 0, "          ");
	printf("    }\n");
}

void command_external_print(t_external *data_external)
{
	printf(RESET WHITE "    external " GRAY "{\n");
	printf("      cmd:     %s'%s'%s\n", CYAN, data_external->args[0], GRAY);
	printf("      args:    ");
	print_str_arr(data_external->args);
	// printf("      fd_in:   %s%d%s\n", PURPLE, data_external->fd_in, GRAY);
	// printf("      fd_out:  %s%d%s\n", PURPLE, data_external->fd_out, GRAY);
	// heredoc_print(&data_external->heredoc);
	printf("    }\n");
}

void	command_print(t_command *command)
{
	if(command->type == COMMAND_BUILTIN_ECHO)
		command_builtin_echo_print(&command->data.builtin_echo);
	if(command->type == COMMAND_BUILTIN_CD)
		command_builtin_cd_print(&command->data.builtin_cd);
	if(command->type == COMMAND_BUILTIN_PWD)
		command_builtin_pwd_print();
	if(command->type == COMMAND_BUILTIN_EXPORT)
		command_builtin_export_print(&command->data.builtin_export);
	if(command->type == COMMAND_BUILTIN_UNSET)
		command_builtin_unset_print(&command->data.builtin_unset);
	if(command->type == COMMAND_BUILTIN_ENV)
		command_builtin_env_print();
	if(command->type == COMMAND_BUILTIN_EXIT)
		command_builtin_exit_print(&command->data.builtin_exit);
	if(command->type == COMMAND_EXTERNAL)
		command_external_print(&command->data.external);
}

char	*chain_op_str(t_chain *chain)
{
	if (chain->op == OP_AND)
		return ("&&");
	if (chain->op == OP_OR)
		return ("||");
	return NULL;
}

static void	chain_print(t_chain *chain)
{
	unsigned long	i;
	t_command 		*command;

	i = 0;
	printf(RESET WHITE "  chain " GRAY "[\n");
	while (i < arr_size(&chain->commands))
	{
		command = (t_command *) arr_get(&chain->commands, i);
		command_print(command);
		i++;
	}
	printf("  ]\n");
	printf("  %s%s%s\n", YELLOW, chain_op_str(chain), GRAY);
}

void	sequence_print(t_array *sequence)
{
	unsigned long	i;
	t_chain 		*chain;

	i = 0;
	printf(WHITE "\nsequence " GRAY "[\n");
	while(i < arr_size(sequence))
	{
		chain = (t_chain *) arr_get(sequence, i);
		chain_print(chain);
		i++;
	}
	printf("]\n");
}
