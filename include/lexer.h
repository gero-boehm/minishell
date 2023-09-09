#include "lexerdef.h"
#include "arraydef.h"

#ifndef LEXER_H
# define LEXER_H

int		lexer_boundaries_get(char *str, t_array *boundaries);
int		lexer_fragments_get(char *str, t_array *fragments);
void	lexer_quotes_mark(t_array *fragments);
int		lexer_token_mask_get(t_array *fragments, t_array *mask);
int		lexer_token_ranges_get(t_array *spaces, t_array *token_ranges);
int		lexer_vars_get(t_array *fragments, t_array *vars);
int		lexer_fragments_to_tokens(t_array *fragments, t_array *token_ranges, t_array *tokens);

#endif