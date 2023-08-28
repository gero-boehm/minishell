#include "lexerdef.h"
#include "arraydef.h"

#ifndef LEXER_H
# define LEXER_H

int		lexer_get_boundaries(char *str, t_array *boundaries);
int		lexer_get_fragments(char *str, t_array *fragments);

int		lexer_quotes_unclosed(t_array *fragments);
int		lexer_get_ranges_of_quotes(t_array *fragments, t_array *quote_ranges);
void	lexer_expand_quote_ranges(t_array *fragments, t_array *quote_ranges);

#endif