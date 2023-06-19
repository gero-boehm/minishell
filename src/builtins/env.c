/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:50:25 by christianme       #+#    #+#             */
/*   Updated: 2023/06/19 09:46:18 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

    
int ft_env(void)
{
    extern char **environ;
   
    if (environ == NULL)
        return (1);
    while (*environ != NULL) 
    {
        printf("%s\n", *environ);
        environ++;
    }
    return (0);  
}