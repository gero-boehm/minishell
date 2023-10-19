#include "str.h"

int	return_ambiguous_redir(char *value)
{
	return (str_print_error(1, value, ": ambiguous redirect", NULL));
}
