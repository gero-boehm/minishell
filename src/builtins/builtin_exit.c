#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmddef.h"
#include "global.h"
#include "builtins.h"
#include "error.h"
#include "str.h"
#include "env.h"

int	builtin_exit(t_builtin_exit *data)
{
	long	code;

	if (env_get("--mhss", NULL))
		write(2, "exit\n", 5);
	if (data->arg == NULL)
	{
		clear_history();
		success();
	}
	if (str_to_long_unsafe(data->arg, &code))
		error_numeric_arg_required(data->arg);
	if (data->too_many_args)
		return (return_too_many_args(1));
	clear_history();
	error((unsigned char) code);
	return (255);
}
