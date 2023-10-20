#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "memory.h"

static void	str_normalize(char *str)
{
	unsigned char	c;

	while (*str != '\0')
	{
		c = (unsigned char) *str;
		c %= 52;
		if (c < 26)
			c += 'a';
		else
			c += 'A' - 26;
		*str = (char) c;
		str++;
	}
}

int	str_random(size_t length, char **str)
{
	int		fd;
	size_t	bytes_read;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (1);
	if (mem_alloc_str(length, str))
		return (2);
	bytes_read = read(fd, *str, length);
	if (bytes_read != length)
		return (close(fd), 3);
	str_normalize(*str);
	close(fd);
	return (0);
}
