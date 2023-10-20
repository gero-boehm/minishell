#include "cmddef.h"
#include "serializer.h"
#include "array.h"

static int	serializer_serialize_chain_op(t_op op, t_array *lines)
{
	if (append_str("op", lines))
		return (1);
	if (op == OP_AND && append_str("OP_AND", lines))
		return (2);
	if (op == OP_OR && append_str("OP_OR", lines))
		return (3);
	if (op == OP_END && append_str("OP_END", lines))
		return (4);
	return (0);
}

int	serializer_serialize_chain(t_chain *chain, t_array *lines)
{
	if (append_str("chain", lines))
		return (1);
	if (serializer_serialize_commands(&chain->commands, lines))
		return (2);
	if (serializer_serialize_chain_op(chain->op, lines))
		return (3);
	return (0);
}
