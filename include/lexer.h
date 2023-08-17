#include "lexerdef.h"
#include "arraydef.h"

#ifndef LEXER_H
# define LEXER_H

int	lexer_get_boundaries(char *str, t_array *boundaries);
int	lexer_get_fragments(char *str, t_array *fragments);

#endif