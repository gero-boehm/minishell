#include <stdlib.h>
#include <signal.h>
#include "global.h"

int	set_exit_code(int code)
{
	global()->exit_code = code;
	return (code);
}

void	success(void)
{
	cleanup();
	exit(0);
}

void	error(int code)
{
	cleanup();
	exit(code);
}

void	error_fatal(void)
{
	kill(0, SIGTERM);
}
