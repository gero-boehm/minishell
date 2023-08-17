/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:55:21 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/25 17:17:19 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include "globaldef.h"
#include "global.h"
#include "array.h"
#include "assoc.h"
#include "memory.h"
#include "env.h"
#include "str.h"
#include "wildcard.h"
#include "sequence.h"
#include "tmp.h"
#include "vars.h"

extern char	**environ;

void	arr_print(t_array *arr)
{
	for (unsigned int i = 0; i < arr->size; i++)
	{
		int	element = *((int *) arr_get(arr, i));
		printf("%d ", element);
	}
	printf("\n");
}

// void	arr_print_str(t_array *arr)
// {
// 	for (unsigned int i = 0; i < arr->size; i++)
// 	{
// 		printf("%s\n", *(char **) arr_get(arr, i));
// 	}
// }

// void	arr_print_ptr(t_array *arr)
// {
// 	for (unsigned int i = 0; i < arr->size; i++)
// 	{
// 		printf("%p ", *(void **) arr_get(arr, i));
// 	}
// 	printf("\n");
// }

// void	test_fancy(void)
// {
// 	char *str;

// 	mem_alloc(6, (void **) &str);

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

// 	t_array sequence;

// 	// sequence_factory(F_SINGLE_CHAIN_SINGLE_EXTERNAL, &sequence);
// 	sequence_factory(F_SINGLE_CHAIN_MULTIPLE_EXTERNAL, &sequence);
// 	// sequence_factory(F_SINGLE_CHAIN_MULTIPLE_EXTERNAL_AND_BUILTINS, &sequence);
// 	// sequence_factory(F_SINGLE_CHAIN_SINGLE_EXTERNAL_WITH_HEREDOC, &sequence);
// 	// sequence_factory(F_MULTIPLE_CHAINS_SINGLE_EXTERNAL, &sequence);
// 	// sequence_factory(F_MULTIPLE_CHAINS_SINGLE_EXTERNAL_AND_BUILTINS, &sequence);
// 	// sequence_factory(F_MULTIPLE_CHAINS_MULTIPLE_EXTERNAL_AND_BUILTINS, &sequence);
// 	sequence_print(&sequence);

if (arr_create(&arr, sizeof(int)))
  return (1);
int n = 1;
if (arr_add(&arr, &n))
  return (2);
n = 3;
if (arr_add(&arr, &n))
  return (3);

printf("size: %zu\n", arr.size);
printf("max: %zu\n", arr.max_size);

n = 2;
if(arr_insert_at(&arr, 1, &n))
  return (4);


for(int i = 0; i < arr_size(&arr); i++)
  printf("%d\n", *(int *) arr_get(&arr, i));

printf("size: %zu\n", arr.size);
printf("max: %zu\n", arr.max_size);

// t_array vars0;

// arr_create(&vars0, sizeof(t_var));

// t_var var00;
// var00.key = "USER";
// var00.index = -1;
// var00.range.start = 11;
// var00.range.length = 5;

// t_var var01;
// var01.key = "HOME";
// var01.index = -1;
// var01.range.start = 32;
// var01.range.length = 5;

// arr_add(&vars0, &var00);
// arr_add(&vars0, &var01);

// char *str = strdup("my name is $USER and my home is $HOME");
// printf("%s\n", str);
// vars_expand_str(&vars0, &str);
// printf("%s\n", str);



// t_array vars1;

// arr_create(&vars1, sizeof(t_var));

// t_var var10;
// var10.key = "PWD";
// var10.index = 0;
// var10.range.start = 10;
// var10.range.length = 4;

// t_var var11;
// var11.key = "SHELL";
// var11.index = 1;
// var11.range.start = 15;
// var11.range.length = 6;

// t_var var12;
// var12.key = "TERM";
// var12.index = 1;
// var12.range.start = 25;
// var12.range.length = 5;

// arr_add(&vars1, &var10);
// arr_add(&vars1, &var11);
// arr_add(&vars1, &var12);

// // char **str_arr = {"i am here $PWD", "and i am using $SHELL in $TERM"};
// char **str_arr;
// mem_alloc_str_arr(2, &str_arr);
// str_arr[0] = strdup("i am here $PWD");
// str_arr[1] = strdup("and i am using $SHELL in $TERM");

// char **cursor = str_arr;
// printf("\n");
// while (*cursor != NULL)
// 	printf("%s\n", *cursor++);

// vars_expand_str_arr(&vars1, str_arr);

// cursor = str_arr;
// while (*cursor != NULL)
// 	printf("%s\n", *cursor++);




// char *str;
// str_random(16, &str);
// printf("%s\n", str);

// int	fd;
// tmp_create(&fd);
// tmp_write(fd, "sadjn sjd sad jk");
// tmp_close(fd);


// char *str = strdup("hello shitty world");

// printf("%s\n", str);
// t_range range;
// str_range_of(str, "shitty", 0, &range);

// str_sub_range(&str, &range, "awesome");

// printf("%s\n", str);


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