#include <unistd.h>
#include <stdarg.h>
#include "global.h"
#include "error.h"
#include "array.h"
#include "str.h"

int	str_print_error(int code, ...)
{
	va_list	args;
	char	*str;

	write(2, shell_name(), str_len(shell_name()));
	write(2, ": ", 2);
	va_start(args, code);
	while (1)
	{
		str = va_arg(args, char *);
		if (str == NULL)
			break ;
		write(2, str, str_len(str));
	}
	write(2, "\n", 1);
	va_end(args);
	return (set_exit_code(code));
}
