#ifndef PARSER_H
# define PARSER_H

# include "arraydef.h"
# include "cmddef.h"

int	parser_parse(t_array *tokens);

int	parser_sequence_new(t_array **sequence, unsigned long *index);
int	parser_sequence_parse(t_array *tokens, unsigned long *index, t_array *sequence);

int	parser_chain_parse(t_array *tokens, unsigned long *index, t_chain *chain);

int	parser_command_parse(t_array *tokens, unsigned long *index, t_raw_command *command);

#endif