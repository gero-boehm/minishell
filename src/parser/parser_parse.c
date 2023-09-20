#include "cmddef.h"
#include "array.h"
#include "token.h"
#include "parser.h"

int	parser_parse(t_array *tokens)
{
	unsigned long	index;
	unsigned long	sequence_id;
	t_array			*sequence;

	index = 0;
	if (parser_sequence_new(&sequence, &sequence_id))
		return (1);
	if (parser_sequence_parse(tokens, &index, sequence))
		return (2);
	return (0);
}