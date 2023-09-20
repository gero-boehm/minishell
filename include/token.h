#ifndef TOKEN_H
# define TOKEN_H

# include "tokendef.h"

int	token_is_and(t_token *token);
int	token_is_or(t_token *token);
int	token_is_pipe(t_token *token);
int token_is_operator(t_token *token);

int	token_is_redir_in(t_token *token);
int	token_is_redir_out(t_token *token);
int	token_is_redir_heredoc(t_token *token);
int	token_is_redir_out_append(t_token *token);
int token_is_redir(t_token *token);

#endif