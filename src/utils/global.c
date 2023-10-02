#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "globaldef.h"
#include "cmddef.h"
#include "array.h"
#include "env.h"
#include "str.h"
#include "error.h"
#include "path.h"
#include "memory.h"

static int	global_get_exec_path(char *exec_name, char **exec_path)
{
	char	*cwd;

	if (*exec_name == '/')
		return (str_dup(exec_name, exec_path));
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		error_fatal();
	// TODO: replace str_join with path normalizer
	if (str_join(exec_path, "", cwd, "/", exec_name, NULL))
		return (2);
	if (path_normalize(exec_path))
		return (3);
	return (0);
}

char	*shell_name(void)
{
	return ("miniheaven");
}

t_global	*global(void)
{
	static t_global global;

	return (&global);
}

int	global_init(char *exec_name)
{
	if (arr_create(&global()->allocs, sizeof(void *)))
		return (1);
	if (arr_create(&global()->fds, sizeof(int)))
		return (2);
	if (env_init())
		return (3);
	if (global_get_exec_path(exec_name, &global()->exec_path))
		return (4);
	global()->exit_code = 0;
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

void	set_exit_code(int code)
{
	global()->exit_code = code;
}

void	success(void)
{
	cleanup();
	exit(0);
}
