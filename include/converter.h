#ifndef CONVERTER_H
# define CONVERTER_H

#include "cmddef.h"

int converter_convert(t_raw_command *raw_command, t_command *command);

int	converter_convert_builtin_echo(t_raw_command *raw_command, t_builtin_echo *data);
int	converter_convert_builtin_cd(t_raw_command *raw_command, t_builtin_cd *data);
int converter_convert_builtin_export(t_raw_command *raw_command, t_builtin_export *data);
int converter_convert_builtin_unset(t_raw_command *raw_command, t_builtin_unset *data);
int converter_convert_builtin_exit(t_raw_command *raw_command, t_builtin_exit *data);
int converter_convert_external(t_raw_command *raw_command, t_external *data);

#endif