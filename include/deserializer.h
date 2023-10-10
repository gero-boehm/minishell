#ifndef DESERIALIZER_H
# define DESERIALIZER_H

# include "cmddef.h"
# include "arraydef.h"

int	deserializer_deserialize(const char *str, t_array *sequence);
int	deserializer_deserialize_sequence(t_array *lines, unsigned long *index, t_array *sequence);
int	deserializer_deserialize_chain(t_array *lines, unsigned long *index, t_chain *chain);
int	deserializer_deserialize_commands(t_array *lines, unsigned long *index, t_array *commands);

int	deserializer_deserialize_files(t_array *lines, unsigned long *index, t_array *files);
int	deserializer_deserialize_vars(t_array *lines, unsigned long *index, const char *vars_name, t_array *vars);


int	line_matches(t_array *lines, unsigned long index, const char *match);

#endif