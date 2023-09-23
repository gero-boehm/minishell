#include <stdio.h>
#include "globaldef.h"
#include "error.h"

void	error_what_happened(void)
{
	printf("¯\\_(ツ)_/¯\n");
	error_fatal();
}
