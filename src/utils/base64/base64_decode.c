#include "str.h"
#include "memory.h"

static int	base64_get_output_str(const char *input, size_t len, char **output)
{
	size_t	out_len;

	out_len = (len / 4) * 3;
	if (input[len - 1] == '=')
		out_len--;
	if (input[len - 2] == '=')
		out_len--;
	return (mem_alloc_str(out_len, output));
}

static int	base64_value(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 26);
	if (c >= '0' && c <= '9')
		return (c - '0' + 52);
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	return (-1);
}

int	base64_decode(const char *input, char **output)
{
	unsigned long	i;
	unsigned long	j;
	size_t			len;
	int				bits;
	unsigned int	bytes;

	len = str_len(input);
	if (len == 0)
		return (str_dup("", output));
	if (base64_get_output_str(input, len, output))
		return (1);
	i = 0;
	j = 0;
	bits = 0;
	bytes = 0;
	while (i < len)
	{
		if (input[i] != '=')
		{
			bytes = (bytes << 6) + base64_value(input[i]);
			bits += 6;
		}
		while (bits >= 8)
		{
			(*output)[j++] = (bytes >> (bits - 8)) & 0xFF;
			bits -= 8;
		}
		i++;
	}
	return (0);
}
