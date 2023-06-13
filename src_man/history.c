/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:33:11 by christianme       #+#    #+#             */
/*   Updated: 2023/06/13 12:38:10 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_print_history(void) 
{
    HIST_ENTRY* entry;
    int         i;

    i = 1;

    while (i < history_length) 
    {
        entry = history_get(i);
        if (entry != NULL)
            printf("%d: %s\n", i , entry->line);
        i++;
    }
    return (0);
}