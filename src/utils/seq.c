#include <stdio.h>
#include "cmddef.h"
#include "array.h"
#include "range.h"

#define RED				"\033[31m"
#define GREEN			"\033[32m"
#define YELLOW			"\033[33m"
#define ORANGE			"\033[38;5;216m"
#define WHITE			"\033[37m"
#define PURPLE			"\033[38;2;81;97;205m"
#define TURQUOISE		"\033[38;2;71;176;157m"
#define GRAY			"\033[38;5;245m"
#define RESET			"\033[0m"

static void var_print(t_range *var, char *indent, unsigned long index)
{
	printf(RESET WHITE "%svar " GRAY "%lu {\n", indent, index);
	printf("  %skey:   %s'%s'%s\n", indent, ORANGE, var->meta.var_data.key, GRAY);
	printf("  %sindex: %s%lu%s\n", indent, PURPLE, var->meta.var_data.index, GRAY);
	printf("  %srange: %s%lu..%lu%s\n", indent, PURPLE, range_start(var), range_end(var), GRAY);
	printf("%s}\n", indent);
}

static void vars_print(t_array *vars, char *indent)
{
	for (unsigned long i = 0; i < arr_size(vars); i++)
	{
		t_range *var = (t_range *) arr_get(vars, i);
		var_print(var, indent, i);
	}
}

static void args_print(t_array *args)
{
	for (unsigned long i = 0; i < arr_size(args); i++)
	{
		char *str = *(char **) arr_get(args, i);
		if (i > 0)
			printf(", ");
		printf("%s'%s'%s", ORANGE, str, GRAY);
	}
	printf("\n");
}

static void file_print(t_file *file, unsigned long index)
{
	const char *types[] = {"FILE_IN", "FILE_OUT", "FILE_HEREDOC", "FILE_APPEND"};

	printf(RESET WHITE "        file " GRAY "%lu {\n", index);
	printf("          type: %s%s%s\n", PURPLE, types[file->type], GRAY);
	if (file->type == FILE_HEREDOC)
	{
		printf("          str:  %s'%s'%s\n", ORANGE, file->data.heredoc.str, GRAY);
		printf("          vars: [\n");
		vars_print(&file->data.heredoc.vars, "            ");
		printf("          ]\n");
	}
	else
		printf("          path: %s'%s'%s\n", ORANGE, file->data.path, GRAY);
	printf("        }\n");
}

static void files_print(t_array *files)
{
	for (unsigned long i = 0; i < arr_size(files); i++)
	{
		t_file *file = (t_file *) arr_get(files, i);
		file_print(file, i);
	}
}

static void	command_print(t_raw_command *command, unsigned long index)
{
	printf(RESET WHITE "    command " GRAY "%lu {\n", index);
	printf("      args:       ");
	args_print(&command->args);
	printf("      vars_args:  [\n");
	vars_print(&command->vars_args, "        ");
	printf("      ]\n");
	printf("      files:      [\n");
	files_print(&command->files);
	printf("      ]\n");
	printf("      vars_files: [\n");
	vars_print(&command->vars_files, "        ");
	printf("      ]\n");
	// printf("      fd_in:   %s%d%s\n", PURPLE, data_external->fd_in, GRAY);
	// printf("      fd_out:  %s%d%s\n", PURPLE, data_external->fd_out, GRAY);
	// heredoc_print(&data_external->heredoc);
	printf("    }\n");
}

static char	*chain_op_str(t_chain *chain)
{
	if (chain->op == OP_AND)
		return ("&&");
	if (chain->op == OP_OR)
		return ("||");
	if (chain->op == OP_END)
		return ("END");
	return NULL;
}

static void	chain_print(t_chain *chain, unsigned long index)
{
	unsigned long	i;
	t_raw_command 	*command;

	i = 0;
	printf(RESET WHITE "  chain " GRAY "%lu [\n", index);
	while (i < arr_size(&chain->commands))
	{
		command = (t_raw_command *) arr_get(&chain->commands, i);
		command_print(command, i);
		i++;
	}
	printf("  ]\n");
	printf("\n  %s%s%s\n\n", TURQUOISE, chain_op_str(chain), GRAY);
}

void	sequence_print_raw(t_array *sequence, unsigned long index)
{
	unsigned long	i;
	t_chain 		*chain;

	i = 0;
	printf(RESET WHITE "\nsequence " GRAY "%lu [\n", index);
	while(i < arr_size(sequence))
	{
		chain = (t_chain *) arr_get(sequence, i);
		chain_print(chain, i);
		i++;
	}
	printf("]\n" RESET);
}