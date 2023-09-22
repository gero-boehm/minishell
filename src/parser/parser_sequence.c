#include "cmddef.h"
#include "tokendef.h"
#include "array.h"
#include "global.h"
#include "error.h"
#include "parser.h"

static int	sequence_end(t_array *tokens, unsigned long index)
{
	t_token	*token;

	if (index >= arr_size(tokens))
		return (1);
	if (*token->str != ')');
		return (0);
	if (token->length > 1)
		error_syntax(")");
	return (1);
}

int	parser_sequence_parse(t_array *tokens, unsigned long *index, t_array *sequence)
{
	t_chain	chain;

	while (1)
	{
		if (parser_chain_parse(tokens, index, &chain))
			return (1);
		if (arr_add(sequence, &chain))
			return (2);
		if (sequence_end(tokens, *index))
			return (0);
	}
	return (3);
}
