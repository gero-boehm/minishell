/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:12:43 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/07 16:38:19 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>
# include "strdef.h"
# include "arraydef.h"

size_t	str_len(const char *s);
size_t	str_copyn(char *dst, const char *src);
int		str_split(char *str, char c, t_array *arr);

int		str_range_to_exclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_range_to_inclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_range_from_inclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_range_from_exclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_str_to_inclusive(char *str, char *pattern, unsigned long start, char **sub);
int		str_str_to_exclusive(char *str, char *pattern, unsigned long start, char **sub);
int		str_str_from_inclusive(char *str, char *pattern, unsigned long start, char **sub);
int		str_str_from_exclusive(char *str, char *pattern, unsigned long start, char **sub);

int		str_range_of(char *str, char *pattern, unsigned long start, t_range *range);
int		str_extract_range(char *str, t_range *range, char **sub);
int		str_trim_start(char **str, char *set);
int		str_trim_end(char **str, char *set);
int		str_trim(char **str, char *set);


#endif