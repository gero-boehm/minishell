#include "cmddef.h"
#include "skipdef.h"
#include "array.h"
#include "vars.h"

static int	converter_expand_vars(t_array *values, t_array *vars)
{
	unsigned long	i;
	char			**value;

	i = 0;
	while (i < arr_size(values))
	{
		value = (char **) arr_get(values, i);
		if (vars_expand_str(vars, i, value))
			return (1);
		i++;
	}
	return (0);
}

static int	converter_expand_heredoc(t_array *files)
{
	unsigned long	i;
	t_file			*file;

	i = 0;
	while (i < arr_size(files))
	{
		file = (t_file *) arr_get(files, i);
		if (file->type != FILE_HEREDOC)
			SKIP(i);
		if (vars_expand_str(&file->data.heredoc.vars, 0, &file->data.heredoc.str))
			return (1);
		i++;
	}
	return (0);
}

int	converter_expand(t_raw_command *raw_command)
{
	if (converter_expand_vars(&raw_command->args, &raw_command->vars_args))
		return (1);
	if (converter_expand_vars(&raw_command->files, &raw_command->vars_files))
		return (2);
	if (converter_expand_heredoc(&raw_command->files))
		return (3);
	return (0);
}
