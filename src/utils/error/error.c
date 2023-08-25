#include <stdlib.h>
#include <signal.h>
#include "global.h"

void	error(int code)
{
	cleanup();
	exit(code);
}

void	error_fatal(void)
{
	kill(0, SIGTERM);
}
