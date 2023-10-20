#include "cmddef.h"
#include "deserializer.h"
#include "array.h"
#include "str.h"

static int	deserializer_deserialize_command(
		t_array *lines, unsigned long *index, t_raw_command *command)
{
	if (arr_create(&command->args, sizeof(char *)))
		return (1);
	if (arr_create(&command->files, sizeof(t_file)))
		return (2);
	if (arr_create(&command->vars_args, sizeof(t_range)))
		return (3);
	if (arr_create(&command->vars_files, sizeof(t_range)))
		return (4);
	if (deserializer_deserialize_args(lines, index, &command->args))
		return (5);
	if (deserializer_deserialize_files(lines, index, &command->files))
		return (6);
	if (deserializer_deserialize_vars(
			lines, index, "vars_args", &command->vars_args))
		return (7);
	if (deserializer_deserialize_vars(
			lines, index, "vars_files", &command->vars_files))
		return (8);
	return (0);
}

int	deserializer_deserialize_commands(
		t_array *lines, unsigned long *index, t_array *commands)
{
	t_raw_command	command;

	if (!line_matches(lines, *index, "commands"))
		return (0);
	(*index)++;
	while (1)
	{
		if (!line_matches(lines, *index, "command"))
			break ;
		(*index)++;
		if (deserializer_deserialize_command(lines, index, &command))
			return (1);
		if (arr_add(commands, &command))
			return (2);
	}
	return (0);
}
