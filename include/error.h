
#ifndef ERROR_H
# define ERROR_H

void	error(int code);
void	error_fatal(void);

void	error_command_not_found(char *cmd);
void	error_env_not_set(char *var);
void	error_numeric_arg_required(char *arg);
void	error_no_file_or_dir(char *cmd);

void	return_syntax(char *token);
void	error_syntax(char *token);

#endif