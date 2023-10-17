#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	return_syntax(char *token)
{
	PRINT_ERROR(shell_name(),
		": syntax error near unexpected token `", token, "'\n", NULL);
	set_exit_code(258);
}
