#ifndef ERROR_H
# define ERROR_H

# define __P(_s) write(2, _s, str_len(_s))
# define PRINT_ERROR(...) {char *_s; str_join(&_s, "", __VA_ARGS__); __P(_s);}

void	error(int code);
void	error_fatal(void);

void	error_command_not_found(char *cmd);

void	error_env_not_set(char *var);
int		return_env_not_set(char *var);

void	error_numeric_arg_required(char *arg);

void	error_no_file_or_dir(char *path);
int		return_no_file_or_dir(char *path);

void	return_syntax(char *token);

void	error_permission_denied(char *path);
int		return_permission_denied(char *path);

void	error_not_dir(char *path);
int		return_not_dir(char *path);

void	return_ambiguous_redir(char *value);

int		return_too_many_args(void);

int		return_invalid_identifier(const char *cmd, char *key, char *value);

#endif
