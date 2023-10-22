/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:48:45 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:48:45 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stddef.h>

int		malloc2(size_t count, void **ptr);
int		mem_add(void *ptr);
int		mem_alloc(size_t count, void **ptr);

int		mem_alloc_str_arr(size_t count, char ***arr);
int		mem_alloc_str(size_t count, char **str);

int		mem_free(void *ptr);
void	mem_free_from(unsigned long index);
void	mem_free_str_arr(char **arr);

int		mem_ncmp(const void *s1, const void *s2, size_t n);
void	*mem_ncpy(void *dst, const void *src, size_t n);

void	*mem_nmov(void *dst, const void *src, size_t len);

#endif
