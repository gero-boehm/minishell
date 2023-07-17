/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:12:43 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 15:17:03 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>
# include "strdef.h"
# include "arraydef.h"

size_t	str_len(const char *s);
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
int		str_range_between(char *str, char *pattern, unsigned long start, t_range *range);

size_t	str_cpyn(char *dst, const char *src);
int		str_ncmp(const char *s1, const char *s2, size_t n);
int		str_cmp(const char *s1, const char *s2);
int		str_eq(const char *s1, const char *s2);
int		str_dup(const char *str, char **dup);
int		str_join(char **str, const char *sep, ...);

int		str_extract_range(char *str, t_range *range, char **sub);
int		str_cut_range(char *str, t_range *range, char **sub);

int		str_cut_start(char **str, char *cut);
int		str_cut_end(char **str, char *cut);
int		str_cut(char **str, char *cut);

int		str_trim_start(char **str, char *set);
int		str_trim_end(char **str, char *set);
int		str_trim(char **str, char *set);

int		str_arr_from_arr(t_array *arr, char ***strs);
int		str_from_arr(t_array *arr, char **str);

#endif