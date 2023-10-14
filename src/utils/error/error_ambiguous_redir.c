#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

void	return_ambiguous_redir(char *value)
{
	PRINT_ERROR(shell_name(), ": ", value, ": ambiguous redirect\n", NULL);
	set_exit_code(1);
}
