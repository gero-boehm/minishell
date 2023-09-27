#include "cmddef.h"
#include "array.h"
#include "token.h"
#include "parser.h"
#include "global.h"

int	parser_parse(t_array *tokens, t_array *sequence)
{
	unsigned long	index;

	index = 0;
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);
	if (parser_sequence_parse(tokens, &index, sequence))
		return (2);
	return (0);
}