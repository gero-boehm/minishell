#include <stdlib.h>
#include <unistd.h>
#include "globaldef.h"
#include "array.h"
#include "env.h"
#include "cmddef.h"

t_global	*global(void)
{
	static t_global global;

	return (&global);
}

char	*shell_name(void)
{
	return ("☁️  miniheaven");
}

int	global_init(void)
{
	if (arr_create(&global()->allocs, sizeof(void *)))
		return (1);
	if (arr_create(&global()->fds, sizeof(int)))
		return (2);
	if (arr_create(&global()->heredocs, sizeof(t_heredoc)))
		return (3);
	if (env_init())
		return (4);
	return (0);
}

void	cleanup(void)
{
	size_t	i;
	int		fd;
	void	*ptr;

	i = arr_size(&global()->fds);
	while (i--)
	{
		fd = *(int *) arr_get(&global()->fds, i);
		close(fd);
	}
	i = arr_size(&global()->allocs);
	while (i--)
	{
		ptr = *(void **) arr_get(&global()->allocs, i);
		free(ptr);
	}
}

void	success(void)
{
	cleanup();
	exit(0);
}
