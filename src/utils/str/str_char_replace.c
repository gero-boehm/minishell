/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:58:07 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:07 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	str_char_replace(char *str, char find, char replace)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == find)
		{
			*str = replace;
			count++;
		}
		str++;
	}
	return (count);
}
