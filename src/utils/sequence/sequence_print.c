<<<<<<< HEAD
// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   sequence_print.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/24 19:21:05 by gbohm             #+#    #+#             */
// /*   Updated: 2023/08/03 17:27:08 by gbohm            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdio.h>
// #include "cmddef.h"
// #include "array.h"

// #define RED				"\033[31m"
// #define GREEN			"\033[32m"
// #define ORANGE			"\033[38;5;216m"
// #define WHITE			"\033[37m"
// #define PURPLE			"\033[38;2;81;97;205m"
// #define TURQUOISE		"\033[38;2;71;176;157m"
// #define GRAY			"\033[38;5;245m"
// #define RESET			"\033[0m"

// void	print_str_arr(char **arr)
// {
// 	int	first = 1;

// 	printf("[");
// 	while (*arr != NULL)
// 	{
// 		if (!first)
// 			printf(", ");
// 		printf("%s'%s'%s", ORANGE, *arr, GRAY);
// 		first = 0;
// 		arr++;
// 	}
// 	printf("]\n");
// }

// void	print_var(t_var *var, char *pre)
// {
// 	printf(RESET WHITE"%s        var " GRAY "{\n", pre);
// 	printf("%s          key:   %s'%s'%s\n", pre, ORANGE, var->key, GRAY);
// 	printf("%s          index: %s%ld%s\n", pre, PURPLE, var->index, GRAY);
// 	printf("%s          range: %s%lu..%lu%s\n", pre, PURPLE, var->range.start, var->range.start + var->range.length, GRAY);
// 	printf("%s        }\n", pre);
// }

// void	print_vars(t_array *vars, char *name, int in_heredoc, char *padding)
// {
// 	char			*pre;
// 	unsigned long	i;
// 	t_var			*var;


// 	i = 0;
// 	pre = in_heredoc ? "  " : "";
// 	printf(RESET WHITE "%s      %s:%s" GRAY "[\n", pre, name, padding);
// 	while (i < arr_size(vars))
// 	{
// 		var = (t_var *) arr_get(vars, i);
// 		print_var(var, pre);
// 		i++;
// 	}
// 	printf("%s      ]\n", pre);
// }

// void	heredoc_print(t_heredoc *heredoc)
// {
// 	printf(RESET WHITE "      heredoc: " GRAY "{\n");
// 	printf("        available: %s%s%s\n", heredoc->available ? GREEN : RED, heredoc->available ? "true" : "false", GRAY);
// 	if (heredoc->available)
// 	{
// 		printf("        expand:    %s%s%s\n", heredoc->expand ? GREEN : RED, heredoc->expand ? "true" : "false", GRAY);
// 		printf("        str:       %s'%s'%s\n", ORANGE, heredoc->str, GRAY);
// 		if (heredoc->expand)
// 		{
// 			print_vars(&heredoc->vars, "vars", 1, "      ");
// 		}
// 	}
// 	printf("      }\n");
// }

// void command_builtin_echo_print(t_builtin_echo *data_echo)
// {
// 	printf(RESET WHITE "    echo " GRAY "{\n");
// 	printf("      str:     %s'%s'%s\n", ORANGE, data_echo->str, GRAY);
// 	printf("      newline: %s%s%s\n", data_echo->newline ? GREEN : RED, data_echo->newline ? "true" : "false", GRAY);
// 	print_vars(&data_echo->vars, "vars", 0, "    ");
// 	printf("    }\n");
// }

// void command_builtin_cd_print(t_builtin_cd *data_cd)
// {
// 	printf(RESET WHITE "    cd " GRAY "{\n");
// 	printf("      path: %s'%s'%s\n", ORANGE, data_cd->path, GRAY);
// 	print_vars(&data_cd->vars, "vars", 0, " ");
// 	printf("    }\n");
// }

// void command_builtin_pwd_print(void)
// {
// 	printf(RESET WHITE "    pwd " GRAY "{\n");
// 	printf("    }\n");
// }

// void command_builtin_export_print(t_builtin_export *data_export)
// {
// 	printf(RESET WHITE "    export " GRAY "{\n");
// 	printf("      key:        %s'%s'%s\n", ORANGE, data_export->key, GRAY);
// 	printf("      value:      %s'%s'%s\n", ORANGE, data_export->value, GRAY);
// 	print_vars(&data_export->key_vars, "key_vars", 0, "   ");
// 	print_vars(&data_export->value_vars, "value_vars", 0, " ");
// 	printf("    }\n");
// }

// void command_builtin_unset_print(t_builtin_unset *data_unset)
// {
// 	printf(RESET WHITE "    unset " GRAY "{\n");
// 	printf("      key:      %s'%s'%s\n", ORANGE, data_unset->key, GRAY);
// 	print_vars(&data_unset->key_vars, "key_vars", 0, " ");
// 	printf("    }\n");
// }

// void command_builtin_env_print(void)
// {
// 	printf(RESET WHITE "    env " GRAY "{\n");
// 	printf("    }\n");
// }

// void command_builtin_exit_print(t_builtin_exit *data_exit)
// {
// 	printf(RESET WHITE "    exit " GRAY "{\n");
// 	printf("      arg:           %s'%s'%s\n", ORANGE, data_exit->arg, GRAY);
// 	printf("      too_many_args: %s%s%s\n", data_exit->too_many_args ? GREEN : RED, data_exit->too_many_args ? "true" : "false", GRAY);
// 	print_vars(&data_exit->vars, "vars", 0, "          ");
// 	printf("    }\n");
// }

// void command_external_print(t_external *data_external)
// {
// 	printf(RESET WHITE "    external " GRAY "{\n");
// 	printf("      args:    ");
// 	print_str_arr(data_external->args);
// 	printf("      fd_in:   %s%d%s\n", PURPLE, data_external->fd_in, GRAY);
// 	printf("      fd_out:  %s%d%s\n", PURPLE, data_external->fd_out, GRAY);
// 	heredoc_print(&data_external->heredoc);
// 	print_vars(&data_external->vars, "vars", 0, "    ");
// 	printf("    }\n");
// }

// void	command_print(t_command *command)
// {
// 	if(command->type == COMMAND_BUILTIN_ECHO)
// 		command_builtin_echo_print(&command->data.builtin_echo);
// 	if(command->type == COMMAND_BUILTIN_CD)
// 		command_builtin_cd_print(&command->data.builtin_cd);
// 	if(command->type == COMMAND_BUILTIN_PWD)
// 		command_builtin_pwd_print();
// 	if(command->type == COMMAND_BUILTIN_EXPORT)
// 		command_builtin_export_print(&command->data.builtin_export);
// 	if(command->type == COMMAND_BUILTIN_UNSET)
// 		command_builtin_unset_print(&command->data.builtin_unset);
// 	if(command->type == COMMAND_BUILTIN_ENV)
// 		command_builtin_env_print();
// 	if(command->type == COMMAND_BUILTIN_EXIT)
// 		command_builtin_exit_print(&command->data.builtin_exit);
// 	if(command->type == COMMAND_EXTERNAL)
// 		command_external_print(&command->data.external);
// }

// char	*chain_op_str(t_chain *chain)
// {
// 	if (chain->op == OP_AND)
// 		return ("&&");
// 	if (chain->op == OP_OR)
// 		return ("||");
// 	return NULL;
// }

// static void	chain_print(t_chain *chain)
// {
// 	unsigned long	i;
// 	t_command 		*command;

// 	i = 0;
// 	printf(RESET WHITE "  chain " GRAY "[\n");
// 	while (i < arr_size(&chain->commands))
// 	{
// 		command = (t_command *) arr_get(&chain->commands, i);
// 		command_print(command);
// 		i++;
// 	}
// 	printf("  ]\n");
// 	if (chain->op != OP_END)
// 		printf("\n  %s%s%s\n\n", TURQUOISE, chain_op_str(chain), GRAY);
// }

// void	sequence_print(t_array *sequence)
// {
// 	unsigned long	i;
// 	t_chain 		*chain;

// 	i = 0;
// 	printf(WHITE "\nsequence " GRAY "[\n");
// 	while(i < arr_size(sequence))
// 	{
// 		chain = (t_chain *) arr_get(sequence, i);
// 		chain_print(chain);
// 		i++;
// 	}
// 	printf("]\n");
// }
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:21:05 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/17 14:12:21 by gbohm            ###   ########.fr       */
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
	printf("    }\n");
}

void command_builtin_cd_print(t_builtin_cd *data_cd)
{
	printf(RESET WHITE "    cd " GRAY "{\n");
	printf("      path: %s'%s'%s\n", ORANGE, data_cd->path, GRAY);
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
>>>>>>> master
