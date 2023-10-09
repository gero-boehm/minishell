#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "base64.h"
#include "memory.h"

int	line_matches(t_array *lines, unsigned long index, const char *match)
{
	char	*line;

	if (index >= arr_size(lines))
		return (0);
	line = *(char **) arr_get(lines, index);
	return (str_eq(line, match));
}

int	deserializer_deserialize_var(t_array *lines, unsigned long *index, t_range *var)
{
	char	*line;
	char	*key;

	if (line_matches(lines, *index, "start"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		// TODO: replace with proper function for type
		if (str_to_long_unsafe(line, &var->start))
			return (1);
		(*index)++;
	}
	if (line_matches(lines, *index, "length"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		// TODO: replace with proper function for type
		if (str_to_long_unsafe(line, &var->length))
			return (2);
		(*index)++;
	}
	if (line_matches(lines, *index, "index"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		// TODO: replace with proper function for type
		if (str_to_long_unsafe(line, &var->meta.var_data.index))
			return (3);
		(*index)++;
	}
	if (line_matches(lines, *index, "key"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		// TODO: replace with proper function for type
		if (str_dup(line, &key))
			return (4);
		var->meta.var_data.key = key;
		(*index)++;
	}
	return (0);
}

int	deserializer_deserialize_vars(t_array *lines, unsigned long *index, const char *vars_name, t_array *vars)
{
	t_range	var;

	if (!line_matches(lines, *index, vars_name))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "var"))
			break ;
		(*index)++;
		if (deserializer_deserialize_var(lines, index, &var))
			return (1);
		if (arr_add(vars, &var))
			return (2);
	}
	return (0);
}

int	deserializer_deserialize_args(t_array *lines, unsigned long *index, t_array *args)
{
	char	*line;
	char	*arg;

	if (!line_matches(lines, *index, "args"))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "arg"))
			break ;
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		if (str_dup(line, &arg))
			return (1);
		if (arr_add(args, &arg))
			return (2);
		(*index)++;
	}
	return (0);
}

void	deserializer_deserialize_file_type(t_array *lines, unsigned long *index, t_file_type *type)
{
	if (!line_matches(lines, *index, "type"))
		return ;
	(*index)++;
	if (line_matches(lines, *index, "FILE_IN"))
		*type = FILE_IN;
	else if (line_matches(lines, *index, "FILE_OUT"))
		*type = FILE_OUT;
	else if (line_matches(lines, *index, "FILE_HEREDOC"))
		*type = FILE_HEREDOC;
	else if (line_matches(lines, *index, "FILE_APPEND"))
		*type = FILE_APPEND;
	(*index)++;
}

int	deserializer_deserialize_file_data_heredoc(t_array *lines, unsigned long *index, t_heredoc *heredoc)
{
	char	*line;

	if (arr_create(&heredoc->vars, sizeof(t_range)))
		return (1);
	if (line_matches(lines, *index, "str"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		if (base64_decode(line, &heredoc->str))
			return (2);
		(*index)++;
	}
	if (deserializer_deserialize_vars(lines, index, "vars", &heredoc->vars))
		return (3);
	return (0);
}

int	deserializer_deserialize_file_data(t_array *lines, unsigned long *index, t_file_data *data)
{
	char	*line;
	char	*path;

	if (!line_matches(lines, *index, "data"))
		return (0);
	(*index)++;
	line = *(char **) arr_get(lines, *index);
	if (line_matches(lines, *index, "heredoc"))
	{
		(*index)++;
		if (deserializer_deserialize_file_data_heredoc(lines, index, &data->heredoc))
			return (1);
	}
	else if (line_matches(lines, *index, "path"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		if (str_dup(line, &path))
			return (2);
		data->path = path;
		(*index)++;
	}
	return (0);
}

int	deserializer_deserialize_file(t_array *lines, unsigned long *index, t_file *file)
{
	deserializer_deserialize_file_type(lines, index, &file->type);
	return (deserializer_deserialize_file_data(lines, index, &file->data));
}

int	deserializer_deserialize_files(t_array *lines, unsigned long *index, t_array *files)
{
	t_file	file;

	if (!line_matches(lines, *index, "files"))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "file"))
			break ;
		(*index)++;
		if (deserializer_deserialize_file(lines, index, &file))
			return (1);
		if (arr_add(files, &file))
			return (2);
	}
	return (0);
}

int	deserializer_deserialize_command(t_array *lines, unsigned long *index, t_raw_command *command)
{
	if (arr_create(&command->args, sizeof(char *)))
		return (1);
	if (arr_create(&command->files, sizeof(t_file)))
		return (2);
	if (arr_create(&command->vars_args, sizeof(t_range)))
		return (3);
	if (arr_create(&command->vars_files, sizeof(t_range)))
		return (4);
	if (deserializer_deserialize_args(lines, index, &command->args))
		return (5);
	if (deserializer_deserialize_files(lines, index, &command->files))
		return (6);
	if (deserializer_deserialize_vars(lines, index, "vars_args", &command->vars_args))
		return (7);
	if (deserializer_deserialize_vars(lines, index, "vars_files", &command->vars_files))
		return (8);
	return (0);
}

int	deserializer_deserialize_commands(t_array *lines, unsigned long *index, t_array *commands)
{
	t_raw_command	command;

	if (!line_matches(lines, *index, "commands"))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "command"))
			break ;
		(*index)++;
		if (deserializer_deserialize_command(lines, index, &command))
			return (1);
		if (arr_add(commands, &command))
			return (2);
	}
	return (0);
}

void	deserializer_deserialize_chain_op(t_array *lines, unsigned long *index, t_op *op)
{
	if (!line_matches(lines, *index, "op"))
		return ;
	(*index)++;
	if (line_matches(lines, *index, "OP_AND"))
		*op = OP_AND;
	else if (line_matches(lines, *index, "OP_OR"))
		*op = OP_OR;
	else if (line_matches(lines, *index, "OP_END"))
		*op = OP_END;
	(*index)++;
}

int	deserializer_deserialize_chain(t_array *lines, unsigned long *index, t_chain *chain)
{
	if (arr_create(&chain->commands, sizeof(t_raw_command)))
		return (1);
	if (deserializer_deserialize_commands(lines, index, &chain->commands))
		return (2);
	deserializer_deserialize_chain_op(lines, index, &chain->op);
	return (0);
}

int	deserializer_deserialize_sequence(t_array *lines, unsigned long *index, t_array *sequence)
{
	t_chain	chain;

	if (arr_create(sequence, sizeof(t_chain)))
		return (1);
	while (1)
	{
		if (!line_matches(lines, *index, "chain"))
			break ;
		(*index)++;
		if (deserializer_deserialize_chain(lines, index, &chain))
			return (2);
		if (arr_add(sequence, &chain))
			return (3);
	}
	return (0);
}

int	deserializer_deserialize(const char *str, t_array *sequence)
{
	char			*raw;
	unsigned long	index;
	t_array			lines;

	if (base64_decode(str, &raw))
		return (1);
	if (arr_create(&lines, sizeof(char *)))
		return (2);
	if (str_split_all(raw, '\n', &lines))
		return (3);
	index = 0;
	if (deserializer_deserialize_sequence(&lines, &index, sequence))
		return (4);
	mem_free(raw);
	arr_free_ptr(&lines);
	return (0);
}