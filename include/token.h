/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:47:50 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:47:52 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "tokendef.h"

int		token_is_operand(t_token *token);
int		token_is_redirection(t_token *token);
int		token_is_parenthesis(t_token *token);

int		token_is(t_token *token, t_token_type type);
int		token_is_any(t_token *token, t_token_type type);

void	token_classify_operator(t_token *token);
void	token_classify_redirection(t_token *token);
void	token_classify_parentheses(t_token *token);
void	token_classify_string(t_token *token);

int		token_classify_operator_and(t_token *token);
int		token_classify_operator_or(t_token *token);
int		token_classify_operator_pipe(t_token *token);

int		token_classify_redirection_in(t_token *token);
int		token_classify_redirection_out(t_token *token);
int		token_classify_redirection_heredoc(t_token *token);
int		token_classify_redirection_append(t_token *token);

int		token_classify_parenthesis_opening(t_token *token);
int		token_classify_parenthesis_closing(t_token *token);

#endif