#include "cmddef.h"
#include "deserializer.h"
#include "array.h"

static void	deserializer_deserialize_chain_op(
		t_array *lines, unsigned long *index, t_op *op)
{
	if (!line_matches(lines, *index, "op"))
		return ;
	(*index)++;
	if (line_matches(lines, *index, "OP_AND"))
		*op = OP_AND;
	else if (line_matches(lines, *index, "OP_OR"))
		*op = OP_OR;
	else if (line_matches(lines, *index, "OP_END"))
		*op = OP_END;
	(*index)++;
}

int	deserializer_deserialize_chain(
		t_array *lines, unsigned long *index, t_chain *chain)
{
	if (arr_create(&chain->commands, sizeof(t_raw_command)))
		return (1);
	if (deserializer_deserialize_commands(lines, index, &chain->commands))
		return (2);
	deserializer_deserialize_chain_op(lines, index, &chain->op);
	return (0);
}
