/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:58:06 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/10 12:15:19 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexerdef.h"
#include "arraydef.h"

#ifndef LEXER_H
# define LEXER_H

int	lexer_get_boundaries(char *str, t_array *boundaries);
int	lexer_get_fragments(char *str, t_array *fragments);

#endif