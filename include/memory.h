/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:48:48 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:30:08 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stddef.h>

int		malloc2(size_t count, void **ptr);
int		memalloc(size_t count, void **ptr);
int		memfree(void *ptr);

int		memalloc_str_arr(size_t	count, char ***arr);
int		memalloc_str(size_t	count, char **str);

int		mem_ncmp(const void *s1, const void *s2, size_t n);
void	*mem_ncpy(void *dst, const void *src, size_t n);


#endif
