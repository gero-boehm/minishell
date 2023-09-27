#ifndef BASE64_H
# define BASE64_H

int	base64_encode(const char *input, char **output);
int base64_decode(const char *input, char **output);

#endif