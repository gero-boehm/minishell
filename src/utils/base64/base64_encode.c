#include "memory.h"
#include "str.h"

const char symbols[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int base64_get_output_str(size_t len, char **output)
{
	size_t out_len;

	out_len = len / 3;
	if (len % 3 != 0)
		out_len++;
	out_len *= 4;
	return (mem_alloc_str(out_len, output));
}

int	base64_encode(const char *input, char **output)
{
	int				i;
	int				j;
	size_t			len;
	unsigned int	bytes;

	len = str_len(input);
	if (base64_get_output_str(len, output))
		return (1);
	i = 0;
	j = 0;
	while (len--) {
		bytes = bytes << 8;
		bytes += (unsigned char) input[i++];
		if (i % 3 == 0) {
			(*output)[j++] = symbols[(bytes >> 18) & 0x3F];
			(*output)[j++] = symbols[(bytes >> 12) & 0x3F];
			(*output)[j++] = symbols[(bytes >> 6) & 0x3F];
			(*output)[j++] = symbols[bytes & 0x3F];
			bytes = 0;
		}
	}
	if (i % 3) {
        bytes <<= (3 - (i % 3)) * 8;
        (*output)[j++] = symbols[(bytes >> 18) & 0x3F];
        (*output)[j++] = symbols[(bytes >> 12) & 0x3F];
        if (i % 3 == 2) {
            (*output)[j++] = symbols[(bytes >> 6) & 0x3F];
        } else {
            (*output)[j++] = '=';
        }
        (*output)[j++] = '=';
    }
	return (0);
}
