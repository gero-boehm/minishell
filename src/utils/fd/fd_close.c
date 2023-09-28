#include <unistd.h>
#include "global.h"
#include "error.h"
#include "array.h"

void	fd_close(int fd)
{
	close(fd);
	if (arr_remove(&global()->fds, &fd))
		error_fatal();
}

void	fd_close_all(void)
{
	unsigned long	i;
	int				fd;

	i = 0;
	while (i < arr_size(&global()->fds))
	{
		fd = *(int *) arr_get(&global()->fds, i);
		close(fd);
		i++;
	}
	global()->fds.size = 0;
}
