#include <unistd.h>
#include <fcntl.h>
#include "global.h"
#include "error.h"
#include "array.h"

int fd_pipe(int ports[2])
{
	if (pipe(ports) == -1)
		return (1);
	if (arr_add(&global()->fds, &ports[0]))
		return (2);
	if (arr_add(&global()->fds, &ports[1]))
		return (3);
	return (0);
}
