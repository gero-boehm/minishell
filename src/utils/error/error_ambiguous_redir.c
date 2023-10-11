#include <stdio.h>
#include "global.h"

void	return_ambiguous_redir(char *value)
{
	printf("%s: %s: ambiguous redirect\n", shell_name(), value);
	set_exit_code(1);
}
