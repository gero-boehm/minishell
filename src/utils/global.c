#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
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
	return ("☁️  miniheaven");
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
	if (arr_create(&global()->heredocs, sizeof(t_heredoc)))
		return (3);
	if (arr_create(&global()->sequences, sizeof(t_array)))
		return (4);
	if (env_init())
		return (5);
	if (global_get_exec_path(exec_name, &global()->exec_path))
		return (6);
	if (str_dup("0", &global()->exit_code))
		return (7);
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

static int	get_count(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		if (n == INT_MIN)
			n = INT_MAX;
		else
			n *= -1;
		count++;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	if (n == INT_MIN)
		return (str_dup("-2147483648", &str), str);
	if (n == 0)
		return (str_dup("0", &str), str);
	count = get_count(n);
	if (mem_alloc_str(count, &str))
		return (NULL);
	str[--count] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n)
	{
		str[--count] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

void	set_exit_code(int code)
{
	// TODO: make this better;
	// printf("code: %d\n", code);
	mem_free(global()->exit_code);
	global()->exit_code = ft_itoa(code);
	if (global()->exit_code == NULL)
		error_fatal();
}

void	success(void)
{
	cleanup();
	exit(0);
}
