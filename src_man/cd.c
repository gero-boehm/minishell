/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:23:56 by christianme       #+#    #+#             */
/*   Updated: 2023/06/15 22:55:03 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// str doesn't needs '/' before the dir name for relative but for absolut
int ft_cd(char *str)
{
    char *path;
    path = NULL;
    
    if (str != NULL)
    {
        if (chdir(str) == -1)
            return (printf("%s\n", "Error"), 1);
        // // Test //
        // printf("after:    %s\n", getcwd(path, 1));
        return (0);
    }
    return (1);
}