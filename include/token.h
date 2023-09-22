#ifndef TOKEN_H
# define TOKEN_H

# include "cmddef.h"
# include "tokendef.h"

int	token_is_and(t_token *token);
int	token_is_or(t_token *token);
int	token_is_pipe(t_token *token);
int token_is_operator(t_token *token);

int	token_is_redir_in(t_token *token);
int	token_is_redir_out(t_token *token);
int	token_is_redir_heredoc(t_token *token);
int	token_is_redir_out_append(t_token *token);
int token_is_possibly_redir(t_token *token);

int token_is_parenthesis_opening(t_token *token);
int token_is_parenthesis_closing(t_token *token);
int token_is_possibly_parenthesis(t_token *token);

int	token_redirection_type_get(t_token *token, t_file *file);

#endif