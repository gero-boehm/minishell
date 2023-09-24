#include "cmddef.h"
#include "array.h"
#include "parser.h"
#include "str.h"
#include "number.h"
#include "global.h"

int parser_subsequence_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_array			sequence;
	char			*exec_path;
	char			*sequence_id;

	if (arr_create(&sequence, sizeof(t_chain)))
		return (1);
	(*index)++;
	if (parser_sequence_parse(tokens, index, &sequence))
		return (2);
	(*index)++;
	if (str_dup(global()->exec_path, &exec_path))
		return (3);
	if (arr_add(&command->args, &exec_path))
		return (4);
	if (lutoa(arr_size(&global()->sequences), &sequence_id))
		return (5);
	if (arr_add(&command->args, &sequence_id))
		return (6);
	if (arr_add(&global()->sequences, &sequence))
		return (7);
	return (0);
}