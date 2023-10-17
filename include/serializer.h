#ifndef SERIALIZER_H
# define SERIALIZER_H

# include "cmddef.h"
# include "arraydef.h"

int	serializer_serialize(t_array *sequence, char **str);
int	serializer_serialize_sequence(t_array *sequence, t_array *lines);
int	serializer_serialize_chain(t_chain *chain, t_array *lines);
int	serializer_serialize_commands(t_array *commands, t_array *lines);

int	serializer_serialize_args(t_array *args, t_array *lines);
int	serializer_serialize_files(t_array *files, t_array *lines);
int	serializer_serialize_vars(
		t_array *vars, const char *vars_name, t_array *lines);

int	append_str(const char *str, t_array *lines);

#endif