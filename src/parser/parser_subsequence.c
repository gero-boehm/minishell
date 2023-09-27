#include "cmddef.h"
#include "array.h"
#include "parser.h"
#include "str.h"
#include "number.h"
#include "global.h"
#include "serializer.h"

int parser_subsequence_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	t_array			sequence;
	char			*exec_path;
	char			*encoded;

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
	if (serializer_serialize(&sequence, &encoded))
		return (5);
	if (arr_add(&command->args, &encoded))
		return (6);
	arr_free(&sequence);
	return (0);
}