#ifndef SEQUENCE_H
# define SEQUENCE_H

# include "cmddef.h"
# include "arraydef.h"

int		sequence_factory(t_factory factory, t_array *sequence);
void	sequence_print(t_array *sequence);

#endif