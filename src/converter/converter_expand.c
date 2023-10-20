#include "cmddef.h"
#include "array.h"
#include "vars.h"
#include "token.h"
#include "error.h"
#include "env.h"
#include "str.h"

static int	converter_is_ambiguous_redir(
		char *path, unsigned long index, t_array *vars)
{
	unsigned long	i;
	t_range			*var;
	char			*expanded;

	i = 0;
	while (i < arr_size(vars))
	{
		var = (t_range *) arr_get(vars, i);
		if (var->meta.var_data.index != index)
		{
			i++;
			continue ;
		}
		if (env_get(var->meta.var_data.key, &expanded))
			return (return_ambiguous_redir(path));
		if (str_contains(expanded, " "))
			return (return_ambiguous_redir(path));
		i++;
	}
	return (0);
}

static void	converter_expand_args(t_array *args, t_array *vars)
{
	unsigned long	i;
<<<<<<< HEAD
	char			**arg;
=======
	char			*arg;
	t_array			split;
>>>>>>> master

	i = 0;
	while (i < arr_size(args))
	{
<<<<<<< HEAD
		arg = (char **) arr_get(args, i);
		if (vars_expand_str(vars, i, arg))
=======
		arg = *(char **) arr_get(args, i);
		if (vars_expand_str_split(arg, vars, i, &split))
>>>>>>> master
			error_fatal();
		if (arr_remove_at(args, i))
			error_fatal();
		if (arr_insert_arr(args, i, &split))
			error_fatal();
		i += arr_size(&split);
		arr_free(&split);
	}
}

static int	converter_expand_files(t_array *files, t_array *vars)
{
	unsigned long	i;
	t_file			*file;

	i = 0;
	while (i < arr_size(files))
	{
		file = (t_file *) arr_get(files, i);
		if (file->type == FILE_HEREDOC)
		{
			i++;
			continue ;
		}
		if (converter_is_ambiguous_redir(file->data.path, i, vars))
			return (1);
		if (vars_expand_str(vars, i, &file->data.path))
			error_fatal();
		i++;
	}
	return (0);
}

static void	converter_expand_heredoc(t_array *files)
{
	unsigned long	i;
	t_file			*file;

	i = 0;
	while (i < arr_size(files))
	{
		file = (t_file *) arr_get(files, i);
		if (file->type != FILE_HEREDOC)
		{
			i++;
			continue ;
		}
		if (vars_expand_str(&file->data.heredoc.vars,
				0, &file->data.heredoc.str))
			error_fatal();
		i++;
	}
}

int	converter_expand(t_raw_command *raw_command)
{
	converter_expand_args(&raw_command->args, &raw_command->vars_args);
	if (converter_expand_files(&raw_command->files, &raw_command->vars_files))
		return (1);
	converter_expand_heredoc(&raw_command->files);
	return (0);
}
