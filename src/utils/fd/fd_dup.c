#include <unistd.h>
#include "global.h"
#include "error.h"
#include "array.h"

int	fd_dup(int fd_old, int *fd_new)
{
	*fd_new = dup(fd_old);
	if (*fd_new == -1)
		return (1);
	if (arr_add(&global()->fds, fd_new))
		error_fatal();
	return (0);
}
