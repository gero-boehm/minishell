
#ifndef ERROR_H
# define ERROR_H

void	error(int code);
void	error_fatal(void);

void	error_command_not_found(char *cmd);
void	error_env_not_set(char *var);

#endif