/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:48:48 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/07 17:31:19 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stddef.h>

int	malloc2(size_t count, void **ptr);
int	memalloc(size_t count, void **ptr);
int	memfree(void *ptr);

#endif
