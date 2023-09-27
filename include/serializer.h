#ifndef SERIALIZER_H
# define SERIALIZER_H

# include "arraydef.h"

int	serializer_serialize(t_array *sequence, char **str);
int	deserializer_deserialize(const char *str, t_array *sequence);


#endif