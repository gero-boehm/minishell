/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:48:29 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:48:30 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "arraydef.h"
# include "cmddef.h"
# include "tokendef.h"

int	parser_parse(t_array *tokens, t_array *sequence);

int	parser_sequence_new(
		t_array **sequence, unsigned long *sequence_id);
int	parser_sequence_parse(
		t_array *tokens, unsigned long *index, t_array *sequence);

int	parser_chain_parse(t_array *tokens, unsigned long *index, t_chain *chain);

int	parser_command_parse(
		t_array *tokens, unsigned long *index, t_raw_command *command);
int	parser_redir_parse(
		t_array *tokens, unsigned long *index, t_raw_command *command);

int	parser_vars_copy(t_token *token, unsigned long index, t_array *vars);

int	parser_subsequence_parse(
		t_array *tokens, unsigned long *index, t_raw_command *command);

#endif