#include "str.h"

int	return_syntax(char *token)
{
	return (str_print_error(258, "syntax error near unexpected token `", token, "'", NULL));
}
