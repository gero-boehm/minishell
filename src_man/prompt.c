/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:54:46 by christianme       #+#    #+#             */
/*   Updated: 2023/06/15 22:55:17 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char *ft_prompt(void)
void ft_prompt(void)
{
    char* input;
    using_history();

    while (1) {
        input = readline(">>"); 
        if (input == NULL)
            break;
        if (input[0] != '\0')
            add_history(input);
            
        // Test //    
        // printf("input:  %s\n", input);
        
        // char* path = "src_man";
        // printf("path:   %s\n", path);
        // ft_cd(path);
        
        // ft_env();
        // ft_pwd();
        // free(input);
        // return (input); 
    }
    
}