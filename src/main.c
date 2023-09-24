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
#include "lexer.h"
#include "error.h"
#include "range.h"
#include "token.h"
#include "parser.h"
#include "number.h"
#include "path.h"

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

int	is_dir(char *path)
{
	struct stat	stats;

	stat(path, &stats);
	return (0);
}

void iterateDirectories(const char *path) {
	DIR *dir;
	struct dirent *entry;

	// Open the directory
	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		return;
	}

	// Iterate over entries in the directory
	while ((entry = readdir(dir)) != NULL) {
		// Skip current directory (.) and parent directory (..)
		if (str_eq(entry->d_name, ".") || str_eq(entry->d_name, ".."))
			continue;

		// Construct the full path of the entry
		char fullpath[PATH_MAX];
		snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);

		// Recurse if the entry is a directory
		printf("%s\n", fullpath);

		if (entry->d_type == DT_DIR) {
			iterateDirectories(fullpath);
		}

		// Process the entry (you can modify this part to suit your needs)
	}

	// Close the directory
	closedir(dir);
}

int	sort_int(void *element1, void *element2)
{
	int a = *(int *) element1;
	int b = *(int *) element2;

	return (b - a);
}

int	main(int argc, char **argv)
{
	t_array arr;

	(void) argc;
	(void) argv;
	global_init(argv[0]);

	printf("%s\n", global()->exec_path);
	// char *num;
	// lutoa(0, &num);
	// printf("%s\n", num);
	// lutoa(1, &num);
	// printf("%s\n", num);
	// lutoa(20, &num);
	// printf("%s\n", num);
	// lutoa(342, &num);
	// printf("%s\n", num);
	// lutoa(-1, &num);
	// printf("%s\n", num);
	// abort();

	// char *paths[] = {
	// 	"hello/./world",
	// 	"hello/../../world",
	// 	"hello/../../world/..",
	// 	".",
	// 	"..",
	// 	"dir/..",
	// 	"/hello/../../world/..",
	// 	"/.",
	// 	"/..",
	// 	"/dir/..",
	// 	"/test/../.dotfile///.",
	// };

	// for (int i = 0; i < sizeof(paths) / sizeof(char *); i++)
	// {
	// 	char *path;
	// 	str_dup(paths[i], &path);
	// 	printf("%s -> ", path);
	// 	path_normalize(&path);
	// 	printf("%s\n", path);
	// }
	// abort();

	t_array fragments;
	t_array mask;
	t_array tokens;
	t_array	token_ranges;
	// char *str = "pwd&&cd /home";
	// char *str = "e\"ch\"o a  'test' && cat <<e''of\"\"";
	// char *str = "t.";
	// char *str = "echo 'a'\"b\"";
	// char *str = "echo 'a\\' 'b'";
	// char *str = "echo 'a'bc\\'def";
	// char *str = "echo 'ab\"c\\''d\"e'fgh";
	// char *str = "echo 00'ab'\"fg\"h";
	// char *str = "echo a'b c'de\"fg\"h";
	// char *str = "echo a' 'b c d e f g h";
	// char *str = "  echo 'a  a'\"'$USER'\"bb'''''''$HOME'\"'\" d";
	// char *str = " ";
	// char *str = "";
	// char *str = "echo a&&echo b";
	// char *str = "echo a&&||(cat /dev/urandom | head -5)";
	// char *str = "echo a|| cat < /home/$USER/test << eof > out$USER >> out_append";
	// char *str = "echo $HOME && echo b | echo test";
	char *str = "echo $HOME && (cat << test) && pwd";
	// char *str = "echo 'a && b'";
	// char *str = "echo 'a &'& b";
	// char *str = "(echo a)(echo b)";
	// char *str = "(echo a) && (echo b)";
	// char *str = "(echo a) && ((echo b))";
	// char *str = "echo a && ((echo b) | cat)";
	if (lexer_fragments_get(str, &fragments))
		return (1);

	// for (unsigned long i = 0; i < arr_size(&fragments); i++)
	// {
	// 	t_fragment *fragment = (t_fragment *) arr_get(&fragments, i);
	// 	printf("\"%s\"\n", fragment->str);
	// }

	printf("\nfragmens\n");
	for (unsigned long i = 0; i < arr_size(&fragments); i++)
	{
		t_fragment *fragment = (t_fragment *) arr_get(&fragments, i);
		printf("\"%s\", ", fragment->str);
	}
	printf("\n");

	for (unsigned long i = 0; i < arr_size(&fragments); i++)
	{
		t_fragment *fragment = (t_fragment *) arr_get(&fragments, i);
		printf(" %-*c   ", fragment->length, fragment->quote == QUOTE_SINGLE ? '\'' : fragment->quote == QUOTE_DOUBLE ? '"' : 'x');
	}
	printf("\n");

	lexer_quotes_mark(&fragments);

	printf("\nquotes\n");
	for (unsigned long i = 0; i < arr_size(&fragments); i++)
	{
		t_fragment *fragment = (t_fragment *) arr_get(&fragments, i);
		printf("\"%s\", ", fragment->str);
	}
	printf("\n");

	for (unsigned long i = 0; i < arr_size(&fragments); i++)
	{
		t_fragment *fragment = (t_fragment *) arr_get(&fragments, i);
		printf(" %-*c   ", fragment->length, fragment->quote == QUOTE_SINGLE ? '\'' : fragment->quote == QUOTE_DOUBLE ? '"' : 'x');
	}
	printf("\n");

	if (lexer_token_mask_get(&fragments, &mask))
		return (2);

	printf("\nmask\n");
	for (unsigned long i = 0; i < arr_size(&fragments); i++)
	{
		t_fragment *fragment = (t_fragment *) arr_get(&fragments, i);
		printf("\"%s\", ", fragment->str);
	}
	printf("\n");

	for (unsigned long i = 0; i < arr_size(&fragments); i++)
	{
		t_fragment *fragment = (t_fragment *) arr_get(&fragments, i);
		int value = *(int *) arr_get(&mask, i);
		printf(" %-*d   ", fragment->length, value);
	}
	printf("\n");

	if (lexer_token_ranges_get(&mask, &token_ranges))
		return (3);

	printf("\ntoken ranges\n");
	for (unsigned long i = 0; i < arr_size(&token_ranges); i++)
	{
		t_range *range = (t_range *) arr_get(&token_ranges, i);

		printf("%lu..%lu\n", range_start(range), range_end(range));
	}


	if (lexer_fragments_to_tokens(&fragments, &token_ranges, &tokens))
		return (4);

	printf("\ntokens\n");
	for (unsigned long i = 0; i < arr_size(&tokens); i++)
	{
		t_token *token = (t_token *) arr_get(&tokens, i);
		printf("\"%s\", ", token->str);
	}
	printf("\n");

	for (unsigned long i = 0; i < arr_size(&tokens); i++)
	{
		t_token *token = (t_token *) arr_get(&tokens, i);
		printf(" %-*d   ", token->length, token->contained_quotes);
	}
	printf("\n");


	// printf("\nvars\n");
	// for (unsigned long i = 0; i < arr_size(&tokens); i++)
	// {
	// 	t_token *token = (t_token *) arr_get(&tokens, i);
	// 	printf("\"%s\"\n", token->str);

	// 	for (unsigned long j = 0; j < arr_size(&token->vars); j++)
	// 	{
	// 		t_range *var = (t_range *) arr_get(&token->vars, j);
	// 		printf("%s> %lu..%lu, ", var->meta.var_data.key, range_start(var), range_end(var));
	// 	}
	// 	printf("\n\n");
	// }

	lexer_tokens_classify(&tokens);

	if (lexer_tokens_validate(&tokens))
		return (5);


	printf("\n");

	if (parser_parse(&tokens))
		return (6);

	for(unsigned long i = 0; i < arr_size(&global()->sequences); i++)
	{
		t_array	*sequence = (t_array *) arr_get(&global()->sequences, i);
		sequence_print_raw(sequence, i);
	}

	// if (lexer_quotes_indices(&fragments, &indices))
	// 	return (2);

	// for (unsigned long i = 0; i < arr_size(&indices); i++)
	// {
	// 	t_quote_index *qi = (t_quote_index *) arr_get(&indices, i);
	// 	printf("%c %lu %zu\n", qi->quote == QUOTE_SINGLE ? '\'' : '"', qi->index, qi->count);
	// }

	// printf("\nranges\n");
	// if (lexer_quotes_get(&indices, &ranges.quote_ranges))
	// 	return (3);

	// for (unsigned long i = 0; i < arr_size(&ranges.quote_ranges); i++)
	// {
	// 	t_range *range = (t_range *) arr_get(&ranges.quote_ranges, i);
	// 	printf("%c %lu..%lu\n", range->meta.quote == QUOTE_SINGLE ? '\'' : '"', range->start, range->start + range->length);
	// }

	// t_array array;
	// if (lexer_token_mask_get(&fragments, &ranges.quote_ranges, &array))
	// 	return (4);

	// for (unsigned long i = 0; i < arr_size(&fragments); i++)
	// {
	// 	char *fragment = *(char **) arr_get(&fragments, i);
	// 	printf("\"%s\", ", fragment);
	// }
	// printf("\n");

	// for (unsigned long i = 0; i < arr_size(&fragments); i++)
	// {
	// 	char *fragment = *(char **) arr_get(&fragments, i);
	// 	int keep = *(int *) arr_get(&array, i);
	// 	printf(" %-*d   ", str_len(fragment), keep);
	// }
	// printf("\n");

	// if (lexer_token_ranges_get(&array, &ranges.token_ranges))
	// 	return (5);

	// printf("\ntoken ranges\n");
	// for (unsigned long i = 0; i < arr_size(&ranges.token_ranges); i++)
	// {
	// 	t_range *range = (t_range *) arr_get(&ranges.token_ranges, i);

	// 	printf("%lu..%lu\n", range_start(range), range_end(range));
	// }

	// if (lexer_vars_get(&fragments, &ranges.quote_ranges, &ranges.var_ranges))
	// 	return (5);

	// printf("\nvars:\n");
	// for (unsigned long i = 0; i < arr_size(&ranges.var_ranges); i++)
	// {
	// 	t_range *var = (t_range *) arr_get(&ranges.var_ranges, i);
	// 	printf("%lu \"%s\" %lu..%lu\n", var->meta.var_data.index, var->meta.var_data.key, range_start(var), range_end(var));
	// }

	// printf("\ntokens:\n");
	// if (lexer_fragments_to_tokens(&fragments, &ranges, &tokens))
	// 	return (6);

	// for (unsigned long i = 0; i < arr_size(&tokens); i++)
	// {
	// 	t_token *token = (t_token *) arr_get(&tokens, i);
	// 	printf("\"%s\", ", token->str);
	// }
	// printf("\n");










	// if (lexer_spaces_get(&fragments, &spaces))
	// 	return (4);

	// printf("\nspaces\n");
	// for (unsigned long i = 0; i < arr_size(&spaces); i++)
	// {
	// 	unsigned long *si = *(unsigned long *) arr_get(&spaces, i);
	// 	printf("  %lu\n", si);
	// }

	// if (lexer_token_ranges_get(&spaces, &ranges, &tokens))
	// 	return (4);
	// if (lexer_vars_extract(&fragments, &tokens))
	// 	return (5);

	// printf("\ntoken ranges\n");
	// for (unsigned long i = 0; i < arr_size(&tokens); i++)
	// {
	// 	t_range *range = (t_range *) arr_get(&tokens, i);

	// 	printf("%lu..%lu\n", range_start(range), range_end(range));
	// }

	// printf("\ntokens %zu\n", arr_size(&tokens));
	// for (unsigned long i = 0; i < arr_size(&tokens); i++)
	// {
	// 	t_range *range = (t_range *) arr_get(&tokens, i);

	// 	printf("%lu..%lu > ", range_start(range), range_end(range));

	// 	for (unsigned long j = range_start(range); j < range_end(range); j++)
	// 	{
	// 		char *fragment = *(char **) arr_get(&fragments, j);

	// 		if (j > range_start(range))
	// 			printf(", ");
	// 		printf("\"%s\"", fragment);
	// 	}
	// 	printf("\n");


	// 	printf("quotes: ");
	// 	for (unsigned long j = 0; j < arr_size(&range->meta.token_data.quote_ranges); j++)
	// 	{
	// 		t_range *qr = (t_range *) arr_get(&range->meta.token_data.quote_ranges, j);
	// 		printf(" %c> %lu..%lu", qr->meta.quote == QUOTE_SINGLE ? '\'' : '"', range_start(qr), range_end(qr));
	// 	}
	// 	printf("\n");

	// 	printf("vars:   ");
	// 	for (unsigned long j = 0; j < arr_size(&range->meta.token_data.var_ranges); j++)
	// 	{
	// 		t_range *vr = (t_range *) arr_get(&range->meta.token_data.var_ranges, j);
	// 		printf(" %lu \"%s\"> %lu..%lu", vr->meta.var_data.index, vr->meta.var_data.key, range_start(vr), range_end(vr));
	// 	}
	// 	printf("\n");

	// }

	// t_array	test;
	// if (lexer_fragments_to_tokens(&fragments, &tokens, &test))
	// 	return (6);

	// for (unsigned long i = 0; i < arr_size(&fragments); i++)
	// {
	// 	char *fragment = *(char **) arr_get(&fragments, i);
	// 	int keep = *(int *) arr_get(&test, i);
	// 	printf("\"%s\", ", fragment);
	// }
	// printf("\n");

	// for (unsigned long i = 0; i < arr_size(&fragments); i++)
	// {
	// 	char *fragment = *(char **) arr_get(&fragments, i);
	// 	int keep = *(int *) arr_get(&test, i);
	// 	printf(" %-*d   ", str_len(fragment), keep);
	// 	// printf("%zu  ", str_len(fragment));
	// }
	// printf("\n");







	// char *str = "this 'is' \ta \n  test.";
	// char *set = " \n\t\r\f\v";

	// t_range range;

	// str_range_of_set(str, set, 9, &range);
	// printf("%lu..%lu\n", range.start, range.start + range.length);

	// if (arr_create(&arr, sizeof(int)))
	// 	return (1);

	// int nums[] = {4, 3, 1, 1, 5, 6, 5};
	// int c = 7;

	// for (int i = 0; i < c; i++)
	// {
	// 	if (arr_add(&arr, nums + i))
	// 		return (2);
	// }

	// for (int i = 0; i < arr_size(&arr); i++)
	// {
	// 	int v = *(int *) arr_get(&arr, i);
	// 	printf("%d ", v);
	// }
	// printf("\n");

	// // int n = 4;
	// // if(arr_insert_at(&arr, 1, &n))
	// // 	return (3);

	// if (arr_sort(&arr, sort_int))
	// 	return (3);

	// for (int i = 0; i < arr_size(&arr); i++)
	// {
	// 	int v = *(int *) arr_get(&arr, i);
	// 	printf("%d ", v);
	// }
	// printf("\n");

	// if (arr_create(&arr, sizeof(int)))
	// 	return (1);
	// int n = 1;
	// if (arr_add(&arr, &n))
	// 	return (2);
	// n = 3;
	// if (arr_add(&arr, &n))
	// 	return (3);

	// printf("size: %zu\n", arr.size);
	// printf("max: %zu\n", arr.max_size);

	// n = 2;
	// if(arr_insert_at(&arr, 1, &n))
	// 	return (4);


	// for(int i = 0; i < arr_size(&arr); i++)
	// 	printf("%d\n", *(int *) arr_get(&arr, i));

	// printf("size: %zu\n", arr.size);
	// printf("max: %zu\n", arr.max_size);

	// for(int i = 0; i < arr_size(&global()->allocs); i++)
	// 	printf("%p\n", *(void **) arr_get(&global()->allocs, i));

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



	// t_array sequence;

	// sequence_factory(F_SINGLE_CHAIN_SINGLE_BUILTIN, &sequence);
	// sequence_factory(F_SINGLE_CHAIN_SINGLE_EXTERNAL, &sequence);
	// sequence_factory(F_SINGLE_CHAIN_MULTIPLE_EXTERNAL, &sequence);
	// sequence_factory(F_SINGLE_CHAIN_MULTIPLE_EXTERNAL_AND_BUILTINS, &sequence);
	// sequence_factory(F_SINGLE_CHAIN_SINGLE_EXTERNAL_WITH_HEREDOC, &sequence);
	// sequence_factory(F_MULTIPLE_CHAINS_SINGLE_EXTERNAL, &sequence);
	// sequence_factory(F_MULTIPLE_CHAINS_SINGLE_EXTERNAL_AND_BUILTINS, &sequence);
	// sequence_factory(F_MULTIPLE_CHAINS_MULTIPLE_EXTERNAL_AND_BUILTINS, &sequence);
	// sequence_factory(F_MULTIPLE_CHAINS_ALL_BUILTINS, &sequence);
	// sequence_print(&sequence);

	// if (arr_create(&arr, sizeof(char *)))
	// 	return (1);

	// char *a = "a";
	// arr_add(&arr, &a);
	// char *b = "b";
	// arr_add(&arr, &b);
	// char *c = "c";
	// arr_add(&arr, &c);

	// arr_print_str(&arr);

	// char *str;
	// arr_to_str(&arr, &str);

	// str_join(&str, ", ", "a", "b", "c", NULL);

	// printf("%zu |  %s\n", str_len(str), str);

	// printf("%s\n", argv[1]);
	// get_paths(argv[1], &arr);
	// arr_print_str(&arr);

	// char *str = strdup("__bc_sdbc_b__");
	// str_cut(&str, "_");
	// // printf("%c\n", *str);
	// printf("%s\n", str);

	// char *str = "abbbbc";
	// char *pat = "*a*c*";
	// printf("'%s' '%s' | %d\n", str, pat, is_pattern_matching(str, pat));



	// iterateDirectories("test");



	// arr_print_ptr(&global()->allocs);
	// arr_create(&arr, sizeof(int));
	// arr_print_ptr(&global()->allocs);

	// var_set("test", "abc");
	// var_set("abc", "def");
	// arr_print_ptr(&global()->allocs);
	// vars_print();
	// char *v;
	// var_get("test", &v);
	// printf("%s\n", v);

	// t_array split;
	// ft_split("  a b c def ", ' ', &split);

	// arr_print_str(&split);

	// t_range range;
	// char *str = "abc*def";
	// int found = str_range_of("abc*def", "def", 0, &range);
	// printf("%d | %lu -> %zu\n", found, range.start, range.length);

	// char *sub;
	// str_extract_range(str, &range, &sub);
	// printf("%s\n", sub);

	// char *str = strdup("xxxxxx");
	// str_trim(&str, "x");
	// printf("%s\n", str);

	// t_assoc	assoc;
	// int	fail = assoc_from_str_arr(&assoc, envp);

	// assoc_print(&assoc);

	// assoc_init(&assoc);

	// assoc_set(&assoc, "key", "value");
	// assoc_set(&assoc, "test", "123");

	// printf("===============\n");

	// char **arr;
	// assoc_to_str_arr(&assoc, &arr);

	// while (*arr != NULL)
	// 	printf("%s\n", *arr++);

	// while (*arr != NULL)
	// 	printf("%d\n", strcmp(*arr++, *envp++));

	// assoc_print(&global()->env);
	// printf("===============\n");


	// char **env;
	// env_get_all(&env);

	// while (*env != NULL)
	// 	printf("%s\n", *env++);

	// printf("%d\n", strncmp("abcdef", "abc", 3));

	// char *paths;
	// env_get("PATH", &paths);

	// printf("%s\n", paths);
	// env_set("VAR", "test");

	// env_get("VAR", &paths);

	// printf("%s\n", paths);


	// while (*envp != NULL)
	// 	printf("%d\n", strcmp(*envp++, *environ++));
	// printf("===============\n");
	// while (*environ != NULL)
		// printf("%s\n", *environ++);


	// error(0);
	cleanup();
	return (0);
}