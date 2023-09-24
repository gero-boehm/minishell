#ifndef TOKEN_H
# define TOKEN_H

# include "cmddef.h"
# include "tokendef.h"

int	token_is(t_token *token, t_token_type type);
int	token_is_any(t_token *token, t_token_type type);

#endif