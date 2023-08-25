#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include "cmddef.h"
#include "builtins.h"
#include "error.h"
#include "str.h"

static void	ret_too_many_args(void)
{
	printf("miniheaven: exit: too many arguments\n");
}

static void	err_numeric_value_required(char *arg)
{
	printf("miniheaven: exit: %s: numeric argument required\n", arg);
	error(255);
}

int	builtin_exit(t_builtin_exit *data)
{
	long	code;

	printf("exit\n");
	// TODO: rework to handle edge case: when first arg is numeric but too many args, shell will NOT exit. if too many args, but just garbage, shell WILL exit
	if (data->too_many_args)
		return (ret_too_many_args(), 1);
	if (data->arg == NULL)
		return (clear_history(), 0);
	if (str_to_long_unsafe(data->arg, &code))
		return (err_numeric_value_required(data->arg), 255);
	clear_history();
	error((unsigned char) code);
	return (255);
}
