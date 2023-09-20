#include "cmddef.h"
#include "array.h"
#include "token.h"
#include "parser.h"

static int	chain_end(t_array *tokens, unsigned long index, t_chain *chain)
{
	t_token	*token;

	if (index >= arr_size(tokens))
		return (chain->op = OP_END, 1);
	token = (t_token *) arr_get(tokens, index);
	if (token_is_and(token))
		return (chain->op = OP_AND, 1);
	if (token_is_or(token))
		return (chain->op = OP_OR, 1);
	return (0);

}

int	parser_chain_parse(t_array *tokens, unsigned long *index, t_chain *chain)
{
	t_raw_command	command;

	if (arr_create(&chain->commands, sizeof(t_raw_command)))
		return (1);
	while (1)
	{
		if (parser_command_parse(tokens, index, &command))
			return (2);
		if (arr_add(&chain->commands, &command))
			return (3);
		if (chain_end(tokens, *index, chain))
			return ((*index)++, 0);
	}
	return (4);
}
