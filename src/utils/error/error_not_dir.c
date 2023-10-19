#include "error.h"
#include "str.h"

void	error_not_dir(char *path)
{
	str_print_error(1, "cd: ", path, ": Not a directory", NULL);
	error(1);
}

int	return_not_dir(char *path)
{
	return (str_print_error(1, "cd: ", path, ": Not a directory", NULL));
}
