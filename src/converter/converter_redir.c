#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cmddef.h"
#include "global.h"
#include "array.h"
#include "str.h"
#include "fd.h"
#include "error.h"

static int	redir_file_is_in(t_file *file)
{
	return (file->type == FILE_IN || file->type == FILE_HEREDOC);
}

static int	redir_file_open_heredoc(t_file *file, int *fd)
{
	size_t	len;
	int		ports[2];

	// TODO: add function for pipes to add them to fds array
	if (pipe(ports) == -1)
		return (1);
	len = str_len(file->data.heredoc.str);
	write(ports[1], file->data.heredoc.str, len);
	close(ports[1]);
	*fd = ports[0];
	return (0);
}

static int	redir_file_open(t_file *file, int *fd)
{
	int	flags;

	// TODO: handle spaces in path (ambiguous redir)
	if (*fd != STDIN_FILENO && *fd != STDOUT_FILENO)
		fd_close(*fd);
	if (file->type == FILE_IN)
		flags = O_RDONLY;
	if (file->type == FILE_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (file->type == FILE_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	if (file->type == FILE_HEREDOC)
		return (redir_file_open_heredoc(file, fd));
	if (fd_open(file->data.path, flags, 0644, fd))
		return (return_no_file_or_dir(file->data.path, 0), 2);
	return (0);
}

int	converter_redir(t_array *files, t_command *command)
{
	unsigned long	i;
	t_file			*file;
	int				*fd;

	i = 0;
	while (i < arr_size(files))
	{
		file = (t_file *) arr_get(files, i);
		if (redir_file_is_in(file))
			fd = &command->fd_in;
		else
			fd = &command->fd_out;
		if (redir_file_open(file, fd))
			return (1);
		i++;
	}
	return (0);
}
