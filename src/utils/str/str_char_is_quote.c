/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_is_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:11 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:12 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	str_char_is_quote(char c)
{
	return (c == '\'' || c == '"');
}
