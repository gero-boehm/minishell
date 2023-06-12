/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:54:46 by christianme       #+#    #+#             */
/*   Updated: 2023/06/12 19:14:02 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char *ft_prompt(void)
void ft_prompt(void)
{
    char* input;

    while (1) {
        input = readline(">>"); 
        if (input == NULL)
            break;
       if (input[0] != '\0')
            add_history(input);
            
        // Test //    
        printf("Input: %s\n", input);
        // free(input);
        // return (input);
    }
    // return (0);
}