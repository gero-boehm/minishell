#include <stdio.h>
#include "builtins.h"
#include "cmddef.h"
#include "error.h"

void	builtin_echo(t_builtin_echo	*echo)
{
	if (echo->str == NULL)
		echo->str = "";
	printf("%s", echo->str);
	if (echo->newline)
		printf("\n");
	error(0);
}
