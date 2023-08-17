#ifndef ARRAYDEF_H
# define ARRAYDEF_H

# include <stddef.h>

typedef struct s_array {
	void			*elements;
	size_t			size;
	size_t			max_size;
	unsigned int	bytes;
}	t_array;

#endif