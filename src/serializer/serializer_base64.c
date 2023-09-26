#include "memory.h"
#include "str.h"

const char symbols[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int get_encode_str(size_t len, char **str)
{
	size_t out_len;

	out_len = len / 3;
	if (len % 3 != 0)
		out_len++;
	out_len *= 4;
	return (mem_alloc_str(out_len, str));
}

int	serializer_base64_encode(const char *str, char **encoded)
{
	int				i;
	int				j;
	size_t			len;
	unsigned int	bytes;

	len = str_len(str);
	if (get_encode_str(len, encoded))
		return (1);
	i = 0;
	j = 0;
	while (len--) {
		bytes = bytes << 8;
		bytes += (unsigned char) str[i++];
		if (i % 3 == 0) {
			(*encoded)[j++] = symbols[(bytes >> 18) & 0x3F];
			(*encoded)[j++] = symbols[(bytes >> 12) & 0x3F];
			(*encoded)[j++] = symbols[(bytes >> 6) & 0x3F];
			(*encoded)[j++] = symbols[bytes & 0x3F];
			bytes = 0;
		}
	}
	if (i % 3) {
        bytes <<= (3 - (i % 3)) * 8;
        (*encoded)[j++] = symbols[(bytes >> 18) & 0x3F];
        (*encoded)[j++] = symbols[(bytes >> 12) & 0x3F];
        if (i % 3 == 2) {
            (*encoded)[j++] = symbols[(bytes >> 6) & 0x3F];
        } else {
            (*encoded)[j++] = '=';
        }
        (*encoded)[j++] = '=';
    }
	return (0);
}