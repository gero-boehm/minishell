#include "cmddef.h"
#include "array.h"
#include "parser.h"
#include "str.h"
#include "number.h"
#include "global.h"
#include "error.h"

int parser_subsequence_parse(t_array *tokens, unsigned long *index, t_raw_command *command)
{
	// TODO: add error check for incorrect parentheses
	t_array			sequence;
	char			*exec_path;
	char			*sequence_id;

	if (arr_create(&sequence, sizeof(t_chain)))
		error_fatal();
	(*index)++;
	if (parser_sequence_parse(tokens, index, &sequence))
		return (1);
	if (str_dup(global()->exec_path, &exec_path))
		error_fatal();
	if (arr_add(&command->args, &exec_path))
		error_fatal();
	if (lutoa(arr_size(&global()->sequences), &sequence_id))
		error_fatal();
	if (arr_add(&command->args, &sequence_id))
		error_fatal();
	if (arr_add(&global()->sequences, &sequence))
		error_fatal();
	return (0);
}