#include "str.h"
#include "memory.h"

static int	base64_get_output_str(const char *input, size_t len, char **output)
{
	size_t			out_len;

	out_len = (len * 3) / 4;
    if (input[len - 1] == '=')
		out_len--;
    if (input[len - 2] == '=')
		out_len--;
	return (mem_alloc_str(out_len, output));
}

static int base64_value(char c)
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

int base64_decode(const char *input, char **output)
{
	int 			i;
	int 			j;
	int 			k;
	int 			len;
	unsigned int	bytes;

	len = str_len(input);
	if (base64_get_output_str(input, len, output))
		return (1);
	i = 0;
	j = 0;
	while (i < len) {
		k = 0;
		bytes = 0;
		while (k < 4 && i < len) {
			if (input[i] != '=') {
				bytes = bytes << 6;
				bytes += base64_value(input[i]);
			} else {
				bytes = bytes << (6 * (4 - k));
				break;
			}
			k++;
			i++;
		}
		(*output)[j++] = (bytes >> 16) & 0xFF;
		if (input[i - 2] != '=') (*output)[j++] = (bytes >> 8) & 0xFF;
		if (input[i - 1] != '=') (*output)[j++] = bytes & 0xFF;
	}
	return (0);
}
