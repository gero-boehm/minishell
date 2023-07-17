/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:24:14 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/17 18:52:57 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include "array.h"
#include "str.h"

static int	opendir2(const char *path, DIR **dir)
{
	*dir = opendir(path);
	return (*dir == NULL);
}

static int	readdir2(DIR *dir, struct dirent **entry)
{
	errno = 0;
	*entry = readdir(dir);
	return (errno);
}

static size_t	get_length_of_subpattern(char *pattern)
{
	t_range	range;

	if (*pattern == '\0')
		return (0);
	if (!str_range_to_exclusive(pattern, "*", 0, &range))
		return (range.length);
	return (str_len(pattern));
}

int	is_pattern_matching(char *name, char *pattern)
{
	int		wildcard;
	size_t	len;

	if (str_eq(pattern, "*"))
		return (1);
	while (1)
	{
		wildcard = *pattern == '*';
		pattern += wildcard;
		while (1)
		{
			if (*pattern == '\0')
				return (*name == '\0');
			len = get_length_of_subpattern(pattern);
			if (str_ncmp(name, pattern, len) == 0)
			{
				name += len;
				pattern += len;
				break ;
			}
			else if (wildcard)
				name++;
			else
				return (0);
		}
	}
}

static int	is_dir_current_or_parent(char name[PATH_MAX])
{
	return (str_eq(name, ".") || str_eq(name, ".."));
}

// static int	get_sub_path(char *path, char name[PATH_MAX], char **sub_path)
// {
// 	if (*path == '\0')
// 		return (str_dup(path, sub_path));

// 	return (str_join(&sub_path, "/", path, entry->d_name, NULL))
// }

static int	recurse(char *path, char **patterns, t_array *paths)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*sub_path;

	if (*patterns == NULL)
	{
		if (arr_add(paths, &path))
			return (6);
		return (0);
	}
	if (opendir2(path, &dir))
		return (1);
	while (1)
	{
		if (readdir2(dir, &entry))
			return (closedir(dir), 2);
		if (entry == NULL)
			break ;
		if (is_dir_current_or_parent(entry->d_name))
			continue ;
		if (is_pattern_matching((char *) entry->d_name, *patterns))
		{
			if (str_join(&sub_path, "/", path, entry->d_name, NULL))
				return (closedir(dir), 3);
			if (entry->d_type != DT_DIR)
			{
				if (arr_add(paths, &sub_path))
					return (closedir(dir), 4);
			}
			else if (entry->d_type == DT_DIR)
			{
				if (recurse(sub_path, patterns + 1, paths))
					return (closedir(dir), 5);
			}
		}
	}
	closedir(dir);
	return (0);
}

static int	cwd_get(char *cwd[PATH_MAX])
{
	return (getcwd(cwd, PATH_MAX) == NULL);
}

static int	cwd_cut(char cwd[PATH_MAX], t_array *paths)
{
	char			**path;
	unsigned long	i;

	i = 0;
	while (i < arr_size(paths))
	{
		path = arr_get(paths, i);
		if (str_cut_start(path, cwd))
			return (1);
		i++;
	}
	return (0);
}

int	get_paths(char *pattern, t_array *paths)
{
	t_array	arr;
	char	**parts;
	char	cwd[PATH_MAX];

	if (str_split(pattern, '/', &arr))
		return (1);
	if (str_arr_from_arr(&arr, &parts))
		return (2);
	arr_free(&arr);
	// char **t = parts;
	// while (*t)
	// 	printf("%s\n", *t++);
	// replace "." with cwd
	if (arr_create(paths, sizeof(char *)))
		return (3);
	if (cwd_get(&cwd))
		return (4);
	// printf("cwd = %s\n", cwd);
	if (recurse(cwd, parts, paths))
		return (5);
	if (cwd_cut(cwd, paths))
		return (6);
	return (0);
}

// int	compare(char *str, char *pattern)
// {
// 	while()
// }

// int	matches(char *str, char *pattern)
// {

// }