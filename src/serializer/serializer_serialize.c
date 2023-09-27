#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "memory.h"
#include "number.h"
#include "range.h"
#include "base64.h"

static int insert_literal(const char *str, t_array *lines)
{
	char *dup;

	if (str_dup(str, &dup))
		return (1);
	if (arr_add(lines, &dup))
		return (2);
	return (0);
}

static int serializer_serialize_unsigned_long(const char *key, unsigned long *value, t_array *lines)
{
	char	*str;

	if (insert_literal(key, lines))
		return (1);
	if (lutoa(value, &str))
		return (3);
	if (arr_add(lines, &str))
		return (4);
	return (0);
}

static int serializer_serialize_arg(char *arg, t_array *lines)
{
	if (insert_literal("arg", lines))
		return (1);
	if (arr_add(lines, &arg))
		return (2);
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

static int serializer_serialize_file_type(t_file_type type, t_array *lines)
{
	if (insert_literal("type", lines))
		return (1);
	if (type == FILE_IN && insert_literal("FILE_IN", lines))
		return (2);
	if (type == FILE_OUT && insert_literal("FILE_OUT", lines))
		return (3);
	if (type == FILE_HEREDOC && insert_literal("FILE_HEREDOC", lines))
		return (4);
	if (type == FILE_APPEND && insert_literal("FILE_APPEND", lines))
		return (5);
	return (0);
}

static int serializer_serialize_file_data(t_file *file, t_array *lines)
{
	char	*id;

	if (insert_literal("data", lines))
		return (1);
	if (file->type == FILE_HEREDOC)
		return (serializer_serialize_unsigned_long("id", file->data.id, lines) * 2);
	if (insert_literal("path", lines))
		return (3);
	if (arr_add(lines, &file->data.path))
		return (4);
	return (0);
}

static int serializer_serialize_file(t_file *file, t_array *lines)
{
	if (insert_literal("file", lines))
		return (1);
	if (serializer_serialize_file_type(file->type, lines))
		return (2);
	if (serializer_serialize_file_data(file, lines))
		return (3);
	return (0);
}

static int serializer_serialize_files(t_array *files, t_array *lines)
{
	unsigned long	i;
	t_file			*file;

	if (insert_literal("files", lines))
		return (1);
	i = 0;
	while (i < arr_size(files))
	{
		file = (t_file *) arr_get(files, i);
		if (serializer_serialize_file(file, lines))
			return (2);
		i++;
	}
	return (0);
}

static int serializer_serialize_var(t_range *var, t_array *lines)
{
	if (insert_literal("var", lines))
		return (1);
	if (serializer_serialize_unsigned_long("start", range_start(var), lines))
		return (2);
	if (serializer_serialize_unsigned_long("length", range_length(var), lines))
		return (3);
	if (serializer_serialize_unsigned_long("index", var->meta.var_data.index, lines))
		return (4);
	if (insert_literal("key", lines))
		return (1);
	if (arr_add(lines, &var->meta.var_data.key))
		return (6);
	return (0);
}

static int serializer_serialize_vars(t_array *vars, const char *vars_name, t_array *lines)
{
	unsigned long	i;
	t_range			*var;

	if (arr_size(vars) == 0)
		return (0);
	if (insert_literal(vars_name, lines))
		return (1);
	i = 0;
	while (i < arr_size(vars))
	{
		var = (t_range *) arr_get(vars, i);
		if (serializer_serialize_var(var, lines))
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
	if (serializer_serialize_files(&command->files, lines))
		return (3);
	if (serializer_serialize_vars(&command->vars_args, "vars_args", lines))
		return (4);
	if (serializer_serialize_vars(&command->vars_files, "vars_files", lines))
		return (5);
	return (0);
}

static int serializer_serialize_commands(t_array *commands, t_array *lines)
{
	unsigned long	i;
	t_raw_command	*command;

	if (insert_literal("commands", lines))
		return (1);
	i = 0;
	while (i < arr_size(commands))
	{
		command = (t_raw_command *) arr_get(commands, i);
		if (serializer_serialize_command(command, lines))
			return (2);
		i++;
	}
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
	if (insert_literal("chain", lines))
		return (1);
	if (serializer_serialize_commands(&chain->commands, lines))
		return (2);
	if (serializer_serialize_chain_op(chain->op, lines))
		return (3);
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
	char	*raw;

	if (arr_create(&lines, sizeof(char *)))
		return (1);
	serializer_serialize_sequence(sequence, &lines);
	if (str_from_arr(&lines, "\n", &raw))
		return (2);
	if (base64_encode(raw, str))
		return (3);
	mem_free(raw);
	return (0);
}