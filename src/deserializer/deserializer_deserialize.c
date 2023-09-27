#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "base64.h"
#include "memory.h"

int	line_matches(t_array *lines, unsigned long index, const char *match)
{
	char	*line;

	line = *(char **) arr_get(lines, index);
	return (str_eq(line, match));
}

int	deserializer_deseriaize_args(t_array *lines, unsigned long *index, t_array *args)
{
	char	*arg;

	if (!line_matches(lines, *index, "args"))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "arg"))
			break ;
		(*index)++;
		arg = *(char **) arr_get(lines, *index);
		// TODO: dup arg to prevent segfault when freeing lines array
		if (arr_add(args, &arg))
			return (1);
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

int	deserializer_deserialize_file_data(t_array *lines, unsigned long *index, t_file_data *data)
{
	char	*line;
	char	*path;

	if (!line_matches(lines, *index, "data"))
		return (0);
	(*index)++;
	line = *(char **) arr_get(lines, *index);
	if (line_matches(lines, *index, "id"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		if (str_to_long_unsafe(line, &data->id))
			return (1);
	}
	else if (line_matches(lines, *index, "path"))
	{
		(*index)++;
		line = *(char **) arr_get(lines, *index);
		if (str_dup(line, &path))
			return (2);
		data->path = path;
	}
	return (0);
}

int	deserializer_deserialize_file(t_array *lines, unsigned long *index, t_file *file)
{
	deserializer_deserialize_file_type(lines, index, &file->type);
	return (deserializer_deserialize_file_data(lines, index, &file->data));
}

int	deserializer_deseriaize_files(t_array *lines, unsigned long *index, t_array *files)
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
		if (deserializer_deseriaize_file(lines, index, &file))
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
	t_array			*lines;

	if (base64_decode(str, &raw))
		return (1);
	if (arr_create(&lines, sizeof(char *)))
		return (2);
	if (str_split(raw, '\n', &lines))
		return (3);
	index = 0;
	if (deserializer_deserialize_sequence(&lines, &index, sequence))
		return (4);
	mem_free(raw);
	arr_free_ptr(&lines);
	return (0);
}