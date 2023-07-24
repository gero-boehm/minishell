/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_factory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:04:06 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/24 23:47:56 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmddef.h"
#include "array.h"
#include "str.h"
#include "memory.h"

int	single_link_single_external(t_array *sequence)
{
	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);
	if (arr_add(sequence, &chain0))
		return (3);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	command00.data.external.cmd = (char *) "ls";
	char	*args[] = {"ls", "-la", NULL};
	if (mem_alloc_str_arr(2, &command00.data.external.args))
		return (4);
	command00.data.external.args[0] = (char *) "ls";
	command00.data.external.args[1] = (char *) "-la";
	command00.data.external.fd_in = 0;
	command00.data.external.fd_out = 1;
	command00.data.external.heredoc.is_available = 0;
	if (arr_add(&chain0, &command00))
		return (5);
}

int	single_link_single_external_with_heredoc(t_array *sequence)
{
	// if (single_link_single_external(sequence))
	// 	return (1);

	// t_chain		*chain = (t_chain *) sequence->elements;
	// t_command	*command = (t_command *) chain->commands.elements;
	// t_heredoc	*heredoc = &command->data.external.heredoc;

	if (arr_create(sequence, sizeof(t_chain)))
		return (1);

	t_chain chain0;
	chain0.op = OP_END;
	if (arr_create(&chain0.commands, sizeof(t_command)))
		return (2);
	if (arr_add(sequence, &chain0))
		return (3);

	t_command command00;
	command00.type = COMMAND_EXTERNAL;
	command00.data.external.cmd = (char *) "ls";
	char	*args[] = {"ls", "-la", NULL};
	if (mem_alloc_str_arr(2, &command00.data.external.args))
		return (4);
	command00.data.external.args[0] = (char *) "ls";
	command00.data.external.args[1] = (char *) "-la";
	command00.data.external.fd_in = 0;
	command00.data.external.fd_out = 1;
	command00.data.external.heredoc.is_available = 1;
	command00.data.external.heredoc.is_available = 1;
	command00.data.external.heredoc.expand_vars = 1;
	command00.data.external.heredoc.str = (char *) "this is a $TEST.";
	if (arr_create(&command00.data.external.heredoc.vars, sizeof(t_heredoc_var)))
		return (5);

	t_heredoc_var var;
	var.key = (char *) "TEST";
	var.range.start = 10;
	var.range.length = 5;

	if (arr_add(&command00.data.external.heredoc.vars, &var))
		return (6);

	if (arr_add(&chain0, &command00))
		return (7);
}

int	sequence_factory(t_factory factory, t_array *sequence)
{
	if (factory == F_SINGLE_LINK_SINGLE_EXTERNAL)
		return single_link_single_external(sequence);
	// if (factory == F_SINGLE_LINK_MULTIPLE_EXTERNAL)
	// 	return single_link_multiple_external(sequence);
	// if (factory == F_SINGLE_LINK_MULTIPLE_EXTERNAL_AND_BUILTINS)
	// 	return single_link_multiple_external_and_builtins(sequence);
	if  (factory == F_SINGLE_LINK_SINGLE_EXTERNAL_WITH_HEREDOC)
		return single_link_single_external_with_heredoc(sequence);
	// if (factory == F_MULTIPLE_LINKS_SINGLE_EXTERNAL)
	// 	return multiple_links_single_external(sequence);
	// if (factory == F_MULTIPLE_LINKS_SINGLE_EXTERNAL_AND_BUILTINS)
	// 	return multiple_links_single_external_and_builtins(sequence);
	// if (factory == F_MULTIPLE_LINKS_MULTIPLE_EXTERNAL)
	// 	return multiple_links_multiple_external(sequence);
}

