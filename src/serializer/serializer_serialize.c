#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "memory.h"

static int insert_literal(const char *str, t_array *lines)
{
	char *dup;

	if (str_dup(str, &dup))
		return (1);
	if (arr_add(lines, &dup))
		return (2);
	return (0);
}

static int serializer_serialize_arg(char *arg, t_array *lines)
{
	if (insert_literal("arg", lines))
		return (1);
	return (0);
}

static int serializer_serialize_args(t_array *args, t_array *lines)
{
	unsigned long	i;
	char			*arg;

	if (insert_literal("args", lines))
		return (1);
	i = 0;
	while (i < arr_size(args))
	{
		arg = *(char **) arr_get(args, i);
		if (serializer_serialize_arg(arg, lines))
			return (2);
		i++;
	}
	return (0);
}

static int serializer_serialize_command(t_raw_command *command, t_array *lines)
{
	if (insert_literal("command", lines))
		return (1);
	if (serializer_serialize_args(&command->args, lines))
		return (2);
	return (0);
}

static int serializer_serialize_chain_op(t_op op, t_array *lines)
{
	if (insert_literal("op", lines))
		return (1);
	if (op == OP_AND && insert_literal("OP_AND", lines))
		return (2);
	if (op == OP_OR && insert_literal("OP_OR", lines))
		return (3);
	if (op == OP_END && insert_literal("OP_END", lines))
		return (4);
	return (0);
}

static int serializer_serialize_chain(t_chain *chain, t_array *lines)
{
	unsigned long	i;
	t_raw_command	*command;

	if (insert_literal("chain", lines))
		return (1);
	if (insert_literal("commands", lines))
		return (2);
	i = 0;
	while (i < arr_size(&chain->commands))
	{
		command = (t_raw_command *) arr_get(&chain->commands, i);
		if (serializer_serialize_command(command, lines))
			return (3);
		i++;
	}
	if (serializer_serialize_chain_op(chain->op, lines))
		return (4);
	return (0);
}

static int serializer_serialize_sequence(t_array *sequence, t_array *lines)
{
	unsigned long	i;
	t_chain			*chain;

	i = 0;
	while (i < arr_size(sequence))
	{
		chain = (t_chain *) arr_get(sequence, i);
		if (serializer_serialize_chain(chain, lines))
			return (1);
		i++;
	}
	return (0);
}

int	serializer_serialize(t_array *sequence, char **str)
{
	t_array	lines;

	if (arr_create(&lines, sizeof(char *)))
		return (1);
	serializer_serialize_sequence(sequence, &lines);
	if (str_from_arr(&lines, "\n", str))
		return (2);
	return (0);
}