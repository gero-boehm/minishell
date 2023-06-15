/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:56:08 by christianme       #+#    #+#             */
/*   Updated: 2023/06/15 13:00:26 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int ft_echo(token n, char *str)
int ft_echo(int n, char *str)
{
    int i;
    
    i = 0;
    if (str == NULL)
    {
        printf("\n");
        return (1);
    }
    while (str[i + 1] != '\0')
        printf("%c", str[i++]);
    if (!n)
        printf("\n");
    return (0);        
        
}