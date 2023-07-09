/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:24:14 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/09 08:14:31 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include "array.h"
#include "str.h"

// void iterateDirectories(const char *path) {
//     DIR *dir;
//     struct dirent *entry;

//     // Open the directory
//     dir = opendir(path);
//     if (dir == NULL) {
//         perror("opendir");
//         return;
//     }

//     // Iterate over entries in the directory
//     while ((entry = readdir(dir)) != NULL) {
//         // Skip current directory (.) and parent directory (..)
//         if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
//             continue;

//         // Construct the full path of the entry
//         char fullpath[PATH_MAX];
//         snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

//         // Recurse if the entry is a directory
//         if (entry->d_type == DT_DIR) {
//             iterateDirectories(fullpath);
//         }

//         // Process the entry (you can modify this part to suit your needs)
//         printf("%s\n", fullpath);
//     }

//     // Close the directory
//     closedir(dir);
// }

// int	get_paths(char *query, char ***paths)
// {

// }

// int	compare(char *str, char *pattern)
// {
// 	while()
// }

// int	matches(char *str, char *pattern)
// {

// }