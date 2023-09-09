#include "lexerdef.h"
#include "arraydef.h"

#ifndef LEXER_H
# define LEXER_H

int	lexer_get_boundaries(char *str, t_array *boundaries);
int	lexer_get_fragments(char *str, t_array *fragments);

int	lexer_quotes_indices(t_array *fragments, t_array *indices);
int	lexer_quotes_get(t_array *indices, t_array *ranges);
int	lexer_spaces_get(t_array *fragments, t_array *indices);
int	lexer_token_ranges_get(t_array *spaces, t_array *token_ranges);
int	lexer_vars_get(t_array *fragments, t_array *quote_ranges, t_array *vars);
int	lexer_fragments_to_tokens(t_array *fragments, t_array *token_ranges, t_array *tokens);


int	lexer_get_array(t_array *fragments, t_array *quote_ranges, t_array *array);



#endif