/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:46:15 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/06 15:12:05 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexerdef.h"
#include "array.h"

static char *boundaries[] = {" \n\t\r\f\v", "&&", "|", "<", ">", "$", "'", "\"", "\\", "(", ")", NULL};
static char *var_boundaries[] = {" ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "`", "{", "|", "}", "~", NULL};

// int	lexer_str_to_tokens(char *str, t_array *tokens)
// {
// 	if (arr_create(tokens, sizeof(t_token)))
// 		return (1);
// }
