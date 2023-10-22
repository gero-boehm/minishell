/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:48:56 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:48:57 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int		set_exit_code(int code);
void	success(void);

void	error(int code);
void	error_fatal(void);

void	error_command_not_found(char *cmd);

void	error_env_not_set(char *var);
int		return_env_not_set(char *var);

void	error_numeric_arg_required(char *arg);

void	error_no_file_or_dir(char *path, int is_cd);
int		return_no_file_or_dir(char *path, int is_cd);

int		return_syntax(char *token);

void	error_permission_denied(char *path);
int		return_permission_denied(char *path);

void	error_not_dir(char *path);
int		return_not_dir(char *path);

int		return_ambiguous_redir(char *value);

int		return_too_many_args(int is_exit);

int		return_invalid_identifier(const char *cmd, char *key, char *value);

#endif
