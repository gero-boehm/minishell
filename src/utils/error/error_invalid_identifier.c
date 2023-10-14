#include <unistd.h>
#include "global.h"
#include "error.h"
#include "str.h"

int	return_invalid_identifier(const char *cmd, char *key, char *value)
{
	if (value == NULL)
		PRINT_ERROR(shell_name(), ": ", cmd, ": `", key, "': not a valid identifier\n", NULL)
	else
		PRINT_ERROR(shell_name(), ": ", cmd, ": `", key, "=", value, "': not a valid identifier\n", NULL)
	return (set_exit_code(1));
}
