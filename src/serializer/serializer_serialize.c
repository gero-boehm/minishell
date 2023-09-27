#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "memory.h"
#include "number.h"
#include "range.h"
#include "base64.h"

static int append_str(const char *str, t_array *lines)
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

	if (append_str(key, lines))
		return (1);
	if (lutoa(value, &str))
		return (3);
	if (arr_add(lines, &str))
		return (4);
	return (0);
}

static int serializer_serialize_var(t_range *var, t_array *lines)
{
	if (append_str("var", lines))
		return (1);
	if (serializer_serialize_unsigned_long("start", range_start(var), lines))
		return (2);
	if (serializer_serialize_unsigned_long("length", range_length(var), lines))
		return (3);
	if (serializer_serialize_unsigned_long("index", var->meta.var_data.index, lines))
		return (4);
	if (append_str("key", lines))
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
	if (append_str(vars_name, lines))
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

static int serializer_serialize_arg(char *arg, t_array *lines)
{
	if (append_str("arg", lines))
		return (1);
	if (arr_add(lines, &arg))
		return (2);
	return (0);
}

static int serializer_serialize_args(t_array *args, t_array *lines)
{
	unsigned long	i;
	char			*arg;

	if (append_str("args", lines))
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
	if (append_str("type", lines))
		return (1);
	if (type == FILE_IN && append_str("FILE_IN", lines))
		return (2);
	if (type == FILE_OUT && append_str("FILE_OUT", lines))
		return (3);
	if (type == FILE_HEREDOC && append_str("FILE_HEREDOC", lines))
		return (4);
	if (type == FILE_APPEND && append_str("FILE_APPEND", lines))
		return (5);
	return (0);
}

static int serializer_serialize_file_data_heredoc(t_heredoc *heredoc, t_array *lines)
{
	char	*encoded;

	if (append_str("heredoc", lines))
		return (1);
	if (append_str("str", lines))
		return (2);
	if (base64_encode(heredoc->str, &encoded))
		return (3);
	if (arr_add(lines, &encoded))
		return (4);
	if (serializer_serialize_vars(&heredoc->vars, "vars", lines))
		return (5);
	return (0);
}

static int serializer_serialize_file_data(t_file *file, t_array *lines)
{
	char	*id;

	if (append_str("data", lines))
		return (1);
	if (file->type == FILE_HEREDOC)
		return (serializer_serialize_file_data_heredoc(&file->data.heredoc, lines) * 2);
	if (append_str("path", lines))
		return (3);
	if (arr_add(lines, &file->data.path))
		return (4);
	return (0);
}

static int serializer_serialize_file(t_file *file, t_array *lines)
{
	if (append_str("file", lines))
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

	if (append_str("files", lines))
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

static int serializer_serialize_command(t_raw_command *command, t_array *lines)
{
	if (append_str("command", lines))
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

	if (append_str("commands", lines))
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
	if (append_str("op", lines))
		return (1);
	if (op == OP_AND && append_str("OP_AND", lines))
		return (2);
	if (op == OP_OR && append_str("OP_OR", lines))
		return (3);
	if (op == OP_END && append_str("OP_END", lines))
		return (4);
	return (0);
}

static int serializer_serialize_chain(t_chain *chain, t_array *lines)
{
	if (append_str("chain", lines))
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
	// TODO: free lines array and make sure all instances where strings are added to lines are duped to avoid double frees
	mem_free(raw);
	return (0);
}