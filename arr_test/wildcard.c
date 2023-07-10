/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:24:14 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/10 17:05:10 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
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

static int	is_pattern_matching(char *name, char *pattern)
{
	return (str_eq(pattern, "*") || str_eq(name, pattern));
}

static int	is_current_or_parent_dir(char name[PATH_MAX])
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
		if (is_current_or_parent_dir(entry->d_name))
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

// static int	cwd_get(char *cwd[PATH_MAX])
// {
// 	return (getcwd(*cwd, PATH_MAX) == NULL);
// }

int	get_paths(char *pattern, t_array *paths)
{
	t_array	arr;
	char	**parts;
	char	cwd[PATH_MAX];

	if (str_split(pattern, '/', &arr))
		return (1);
	if (arr_to_str_arr(&arr, &parts))
		return (2);
	arr_free(&arr);
	// char **t = parts;
	// while (*t)
	// 	printf("%s\n", *t++);
	// replace "." with cwd
	if (arr_create(paths, sizeof(char *)))
		return (3);
	// if (cwd_get(&cwd))
	// 	return (4);
	// printf("%s\n", cwd);

	if (recurse(".", parts, paths))
		return (5);
	return (0);
}

// int	compare(char *str, char *pattern)
// {
// 	while()
// }

// int	matches(char *str, char *pattern)
// {

// }