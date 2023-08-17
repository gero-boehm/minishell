#include <stdarg.h>
#include "array.h"
#include "str.h"

int	str_join(char **str, const char *sep, ...)
{
	va_list	args;
	t_array	parts;
	char	*part;

	if (arr_create(&parts, sizeof(char *)))
		return (1);
	va_start(args, sep);
	while (1)
	{
		part = va_arg(args, char *);
		if (part == NULL)
			break ;
		if (arr_size(&parts) > 0 && arr_add(&parts, &sep))
			return (va_end(args), 2);
		if (arr_add(&parts, &part))
			return (va_end(args), 3);
	}
	va_end(args);
	if (str_from_arr(&parts, str))
		return (4);
	arr_free(&parts);
	return (0);
}
