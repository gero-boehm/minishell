/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:41:46 by christianme       #+#    #+#             */
/*   Updated: 2023/06/19 09:46:20 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_pwd(void)
{
    char *pwd;
    
    pwd = NULL;
    pwd = getcwd(pwd, 1);
    if (pwd == NULL)
        return (1);
    printf("%s\n", pwd);    
    return (0);
} 