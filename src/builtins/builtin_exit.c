#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include "cmddef.h"
#include "global.h"
#include "builtins.h"
#include "error.h"
#include "str.h"

static void	ret_too_many_args(void)
{
	// printf("%s: exit: too many arguments\n", shell_name());
}

int	builtin_exit(t_builtin_exit *data)
{
	long	code;

	// printf("exit\n");
	if (data->arg == NULL)
	{
		// TODO: should this not call success()? right now it just returns 0 and doesn't exit
		clear_history();
		success();
	}
	if (str_to_long_unsafe(data->arg, &code))
		error(255);
		// error_numeric_arg_required(data->arg);	
	if (data->too_many_args)
		return (1);
		// return (ret_too_many_args(), 1);
	clear_history();
	error((unsigned char) code);
	return (255);
}
