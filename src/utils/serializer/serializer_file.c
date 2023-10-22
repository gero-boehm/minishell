/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:56:00 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:56:01 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "serializer.h"
#include "array.h"
#include "base64.h"

static int	serializer_serialize_file_type(t_file_type type, t_array *lines)
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

static int	serializer_serialize_file_data_heredoc(
		t_heredoc *heredoc, t_array *lines)
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

static int	serializer_serialize_file_data(t_file *file, t_array *lines)
{
	if (append_str("data", lines))
		return (1);
	if (file->type == FILE_HEREDOC)
		return (serializer_serialize_file_data_heredoc(
				&file->data.heredoc, lines) * 2);
	if (append_str("path", lines))
		return (3);
	if (arr_add(lines, &file->data.path))
		return (4);
	return (0);
}

static int	serializer_serialize_file(t_file *file, t_array *lines)
{
	if (append_str("file", lines))
		return (1);
	if (serializer_serialize_file_type(file->type, lines))
		return (2);
	if (serializer_serialize_file_data(file, lines))
		return (3);
	return (0);
}

int	serializer_serialize_files(t_array *files, t_array *lines)
{
	unsigned long	i;
	t_file			*file;

	if (arr_size(files) == 0)
		return (0);
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
