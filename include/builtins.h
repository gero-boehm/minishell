#ifndef BUILTINS_H
# define BUILTINS_H

# include "cmddef.h"

void	builtin_cd(t_builtin_cd *cd);
void	builtin_echo(t_builtin_echo	*echo);
void	builtin_env(void);
void	builtin_exit(void);
void	builtin_export(t_builtin_export	*export);
void	builtin_pwd(void);
void	builtin_unset(t_builtin_unset *unset);

#endif