#ifndef STR_H
# define STR_H

# include <stddef.h>
# include "arraydef.h"
# include "rangedef.h"

size_t	str_len(const char *s);
int		str_split(char *str, char c, t_array *arr);
int		str_split_all(char *str, char c, t_array *arr);

int		str_range_to_exclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_range_to_inclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_range_from_inclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_range_from_exclusive(char *str, char *pattern, unsigned long start, t_range *range);
int		str_str_to_inclusive(char *str, char *pattern, unsigned long start, char **sub);
int		str_str_to_exclusive(char *str, char *pattern, unsigned long start, char **sub);
int		str_str_from_inclusive(char *str, char *pattern, unsigned long start, char **sub);
int		str_str_from_exclusive(char *str, char *pattern, unsigned long start, char **sub);
int		str_range_of(char *str, char *pattern, unsigned long start, t_range *range);
int		str_range_of_set(char *str, char *set, unsigned long start, t_range *range);
int		str_range_between(char *str, char *pattern, unsigned long start, t_range *range);

size_t	str_cpyn(char *dst, const char *src);
int		str_ncmp(const char *s1, const char *s2, size_t n);
int		str_cmp(const char *s1, const char *s2);
int		str_eq(const char *s1, const char *s2);
int		str_dup(const char *str, char **dup);
int		str_join(char **str, const char *sep, ...);

int		str_extract_range(char *str, t_range *range, char **sub);
int		str_sub_range(char **str, t_range *range, char *sub);
int		str_cut_range(char **str, t_range *range);

int		str_cut_start(char **str, char *cut);
int		str_cut_end(char **str, char *cut);
int		str_cut(char **str, char *cut);

int		str_trim_start(char **str, char *set);
int		str_trim_end(char **str, char *set);
int		str_trim(char **str, char *set);

int		str_arr_from_arr_range(t_array *arr, t_range *range, char ***strs);
int		str_arr_from_arr(t_array *arr, char ***strs);
int		str_from_arr_range(t_array *arr, t_range *range, char *sep, char **str);
int		str_from_arr(t_array *arr, char *sep, char **str);

int		str_random(size_t length, char **str);

int		str_char_in_set(const char *set, char c);
int		str_char_repeat(char c, size_t count, char **str);

int		str_char_is_whitespace(char c);
int		str_char_is_quote(char c);

int		str_to_long_unsafe(const char *str, long *num);

int		str_key_value(char *str, char **key, char **value);

int		str_starts_with(char *str, const char *match);

#endif