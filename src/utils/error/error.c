#include <stdlib.h>
#include "global.h"

void	error(int code)
{
	cleanup();
	exit(code);
}

void	error_fatal(void)
{
	error(134);
}
