/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:23:56 by christianme       #+#    #+#             */
/*   Updated: 2023/06/19 09:46:05 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// str doesn't needs '/' before the dir name for relative but for absolut
int ft_cd(char *str)
{
    
    if (str != NULL)
    {
        if (chdir(str) == -1)
            return (printf("%s\n", "Error"), 1);
        // Test //
        //  char *path;
        // path = NULL;
        // printf("after:    %s\n", getcwd(path, 1));
        return (0);
    }
    return (1);
}