/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:21:05 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/24 23:56:09 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cmddef.h"
#include "array.h"

#define BLACK			"\033[30m"
#define RED				"\033[31m"
#define GREEN			"\033[32m"
#define YELLOW			"\033[33m"
#define BLUE			"\033[34m"
#define MAGENTA			"\033[35m"
#define CYAN			"\033[36m"
#define WHITE			"\033[37m"
#define ORANGE			"\033[38;5;208m"
#define PURPLE			"\033[38;5;165m"
#define LIGHT_BLACK		"\033[1m\033[30m"
#define LIGHT_RED		"\033[1m\033[31m"
#define LIGHT_GREEN		"\033[1m\033[32m"
#define LIGHT_YELLOW	"\033[1m\033[33m"
#define LIGHT_BLUE		"\033[1m\033[34m"
#define LIGHT_MAGENTA	"\033[1m\033[35m"
#define LIGHT_CYAN		"\033[1m\033[36m"
#define LIGHT_WHITE		"\033[1m\033[37m"
#define RESET			"\033[0m"

void	print_str_arr(char **arr)
{
	int	first = 1;

	printf("[");
	while (*arr != NULL)
	{
		if (!first)
			printf(", ");
		printf("%s'%s'%s", CYAN, *arr, LIGHT_BLACK);
		first = 0;
		arr++;
	}
	printf("]\n");
}

void	print_heredoc_var(t_heredoc_var *var)
{
	printf(RESET WHITE"          var " LIGHT_BLACK "{\n");
	printf("            key:   %s'%s'%s\n", CYAN, var->key, LIGHT_BLACK);
	printf("            range: %s%d..%d%s\n", PURPLE, var->range.start, var->range.start + var->range.length, LIGHT_BLACK);
	printf("          }\n");
}

void	print_heredoc_vars(t_array *vars)
{
	unsigned long	i;
	t_heredoc_var	*var;

	i = 0;
	printf(RESET WHITE "        vars:         " LIGHT_BLACK "[\n");
	while (i < arr_size(vars))
	{
		var = (t_heredoc_var *) arr_get(vars, i);
		print_heredoc_var(var);
		i++;
	}
	printf("        ]\n");
}

void	heredoc_print(t_heredoc *heredoc)
{
	printf(RESET WHITE "      heredoc: " LIGHT_BLACK "{\n");
	printf("        is_available: %s%s%s\n", heredoc->is_available ? GREEN : RED, heredoc->is_available ? "true" : "false", LIGHT_BLACK);
	if (heredoc->is_available)
	{
		printf("        expand_vars:  %s%s%s\n", heredoc->expand_vars ? GREEN : RED, heredoc->expand_vars ? "true" : "false", LIGHT_BLACK);
		printf("        str:          %s'%s'%s\n", CYAN, heredoc->str, LIGHT_BLACK);
		if (heredoc->expand_vars)
		{
			print_heredoc_vars(&heredoc->vars);
		}
	}
	printf("      }\n");
}

void command_builtin_echo_print(t_command_data *data)
{

}

void command_builtin_cd_print(t_command_data *data)
{

}

void command_builtin_export_print(t_command_data *data)
{

}

void command_builtin_unset_print(t_command_data *data)
{

}

void command_builtin_env_print(t_command_data *data)
{

}

void command_builtin_exit_print(t_command_data *data)
{

}

void command_external_print(t_external *external)
{
	printf(RESET WHITE "    command " LIGHT_BLACK "{\n");
	printf("      cmd:     %s'%s'%s\n", CYAN, external->cmd, LIGHT_BLACK);
	printf("      args:    ");
	print_str_arr(external->args);
	printf("      fd_in:   %s%d%s\n", PURPLE, external->fd_in, LIGHT_BLACK);
	printf("      fd_out:  %s%d%s\n", PURPLE, external->fd_out, LIGHT_BLACK);
	heredoc_print(&external->heredoc);
	printf("    }\n");
}

void	command_print(t_command *command)
{
	if(command->type == COMMAND_BUILTIN_ECHO)
		command_builtin_echo_print(&command->data);
	if(command->type == COMMAND_BUILTIN_CD)
		command_builtin_cd_print(&command->data);
	if(command->type == COMMAND_BUILTIN_EXPORT)
		command_builtin_export_print(&command->data);
	if(command->type == COMMAND_BUILTIN_UNSET)
		command_builtin_unset_print(&command->data);
	if(command->type == COMMAND_BUILTIN_ENV)
		command_builtin_env_print(&command->data);
	if(command->type == COMMAND_BUILTIN_EXIT)
		command_builtin_exit_print(&command->data);
	if(command->type == COMMAND_EXTERNAL)
		command_external_print(&command->data.external);
}

char	*chain_op_str(t_chain *chain)
{
	if (chain->op == OP_AND)
		return ("OP_AND");
	if (chain->op == OP_OR)
		return ("OP_OR");
	if (chain->op == OP_END)
		return ("OP_END");
}

static void	chain_print(t_chain *chain)
{
	unsigned long	i;
	t_command 		*command;

	i = 0;
	printf(RESET WHITE "  chain " LIGHT_BLACK "[\n");
	while(i < arr_size(command))
	{
		command = (t_command *) arr_get(chain, i);
		command_print(command);
		i++;
	}
	printf("  ]\n");
}

void	sequence_print(t_array *sequence)
{
	unsigned long	i;
	t_chain 		*chain;

	i = 0;
	printf(WHITE "\nsequence " LIGHT_BLACK "[\n");
	while(i < arr_size(sequence))
	{
		chain = (t_chain *) arr_get(sequence, i);
		chain_print(chain);
		i++;
	}
	printf("]\n");
}
