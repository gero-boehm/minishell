#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include "builtins.h"
#include "error.h"

void	builtin_exit(void)
{
	printf("exit\n");
	clear_history();
	error(0);
}
