#include "cmddef.h"
#include "deserializer.h"
#include "array.h"
#include "base64.h"
#include "str.h"

static void	deserializer_deserialize_file_type(
		t_array *lines, unsigned long *index, t_file_type *type)
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

static int	deserializer_deserialize_file_data_heredoc(
		t_array *lines, unsigned long *index, t_heredoc *heredoc)
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

static int	deserializer_deserialize_file_data(
		t_array *lines, unsigned long *index, t_file_data *data)
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
		if (deserializer_deserialize_file_data_heredoc(
				lines, index, &data->heredoc))
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

static int	deserializer_deserialize_file(
		t_array *lines, unsigned long *index, t_file *file)
{
	deserializer_deserialize_file_type(lines, index, &file->type);
	return (deserializer_deserialize_file_data(lines, index, &file->data));
}

int	deserializer_deserialize_files(
		t_array *lines, unsigned long *index, t_array *files)
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
