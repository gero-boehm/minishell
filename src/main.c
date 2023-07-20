// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/27 12:55:21 by gbohm             #+#    #+#             */
// /*   Updated: 2023/07/17 18:55:01 by gbohm            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <dirent.h>
// #include <limits.h>
// #include <sys/stat.h>
// #include "globaldef.h"
// #include "global.h"
// #include "array.h"
// #include "assoc.h"
// #include "memory.h"
// #include "env.h"
// #include "str.h"
// #include "wildcard.h"

// extern char	**environ;

// void	arr_print(t_array *arr)
// {
// 	for (unsigned int i = 0; i < arr->size; i++)
// 	{
// 		int	element = *((int *) arr_get(arr, i));
// 		printf("%d ", element);
// 	}
// 	printf("\n");
// }

// // void	arr_print_str(t_array *arr)
// // {
// // 	for (unsigned int i = 0; i < arr->size; i++)
// // 	{
// // 		printf("%s\n", *(char **) arr_get(arr, i));
// // 	}
// // }

// // void	arr_print_ptr(t_array *arr)
// // {
// // 	for (unsigned int i = 0; i < arr->size; i++)
// // 	{
// // 		printf("%p ", *(void **) arr_get(arr, i));
// // 	}
// // 	printf("\n");
// // }

// void	test_fancy(void)
// {
// 	char *str;

// 	memalloc(6, (void **) &str);

// 	error(1);
// }

// void	test_normal(void)
// {
// 	char *str = malloc(6);

// 	error(1);
// }

// int	is_dir(char *path)
// {
// 	struct stat	stats;

// 	stat(path, &stats);
// }

// void iterateDirectories(const char *path) {
// 	DIR *dir;
// 	struct dirent *entry;

// 	// Open the directory
// 	dir = opendir(path);
// 	if (dir == NULL) {
// 		perror("opendir");
// 		return;
// 	}

// 	// Iterate over entries in the directory
// 	while ((entry = readdir(dir)) != NULL) {
// 		// Skip current directory (.) and parent directory (..)
// 		if (str_eq(entry->d_name, ".") || str_eq(entry->d_name, ".."))
// 			continue;

// 		// Construct the full path of the entry
// 		char fullpath[PATH_MAX];
// 		snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);

// 		// Recurse if the entry is a directory
// 		printf("%s\n", fullpath);

// 		if (entry->d_type == DT_DIR) {
// 			iterateDirectories(fullpath);
// 		}

// 		// Process the entry (you can modify this part to suit your needs)
// 	}

// 	// Close the directory
// 	closedir(dir);
// }


// int	main(int argc, char **argv)
// {
// 	t_array arr;

// 	(void) argc;
// 	(void) argv;
// 	global_init();

// 	// if (arr_create(&arr, sizeof(char *)))
// 	// 	return (1);

// 	// char *a = "a";
// 	// arr_add(&arr, &a);
// 	// char *b = "b";
// 	// arr_add(&arr, &b);
// 	// char *c = "c";
// 	// arr_add(&arr, &c);

// 	// arr_print_str(&arr);

// 	// char *str;
// 	// arr_to_str(&arr, &str);

// 	// str_join(&str, ", ", "a", "b", "c", NULL);

// 	// printf("%zu |  %s\n", str_len(str), str);

// 	// printf("%s\n", argv[1]);
// 	// get_paths(argv[1], &arr);
// 	// arr_print_str(&arr);

// 	// char *str = strdup("__bc_sdbc_b__");
// 	// str_cut(&str, "_");
// 	// // printf("%c\n", *str);
// 	// printf("%s\n", str);

// 	// char *str = "abbbbc";
// 	// char *pat = "*a*c*";
// 	// printf("'%s' '%s' | %d\n", str, pat, is_pattern_matching(str, pat));



// 	// iterateDirectories("test");



// 	// arr_print_ptr(&g_global.allocs);
// 	// arr_create(&arr, sizeof(int));
// 	// arr_print_ptr(&g_global.allocs);

// 	// var_set("test", "abc");
// 	// var_set("abc", "def");
// 	// arr_print_ptr(&g_global.allocs);
// 	// vars_print();
// 	// char *v;
// 	// var_get("test", &v);
// 	// printf("%s\n", v);

// 	// t_array split;
// 	// ft_split("  a b c def ", ' ', &split);

// 	// arr_print_str(&split);

// 	// t_range range;
// 	// char *str = "abc*def";
// 	// int found = str_range_of("abc*def", "def", 0, &range);
// 	// printf("%d | %lu -> %zu\n", found, range.start, range.length);

// 	// char *sub;
// 	// str_extract_range(str, &range, &sub);
// 	// printf("%s\n", sub);

// 	// char *str = strdup("xxxxxx");
// 	// str_trim(&str, "x");
// 	// printf("%s\n", str);

// 	// t_assoc	assoc;
// 	// int	fail = assoc_from_str_arr(&assoc, envp);

// 	// assoc_print(&assoc);

// 	// assoc_init(&assoc);

// 	// assoc_set(&assoc, "key", "value");
// 	// assoc_set(&assoc, "test", "123");

// 	// printf("===============\n");

// 	// char **arr;
// 	// assoc_to_str_arr(&assoc, &arr);

// 	// while (*arr != NULL)
// 	// 	printf("%s\n", *arr++);

// 	// while (*arr != NULL)
// 	// 	printf("%d\n", strcmp(*arr++, *envp++));

// 	// assoc_print(&g_global.env);
// 	// printf("===============\n");


// 	// char **env;
// 	// env_get_all(&env);

// 	// while (*env != NULL)
// 	// 	printf("%s\n", *env++);

// 	// printf("%d\n", strncmp("abcdef", "abc", 3));

// 	// char *paths;
// 	// env_get("PATH", &paths);

// 	// printf("%s\n", paths);
// 	// env_set("VAR", "test");

// 	// env_get("VAR", &paths);

// 	// printf("%s\n", paths);


// 	// while (*envp != NULL)
// 	// 	printf("%d\n", strcmp(*envp++, *environ++));
// 	// printf("===============\n");
// 	// while (*environ != NULL)
// 		// printf("%s\n", *environ++);


// 	// error(0);
// 	cleanup();
// 	return (0);
// }