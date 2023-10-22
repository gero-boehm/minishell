/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:48:42 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:48:43 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "arraydef.h"
# include "cmddef.h"

int		prompt(char **input);
void	exec_sequence(t_array *sequence);

int		read_input(char **str);

void	signals(void);

int		exec_chain(t_chain *chain, int *fd_stdin, int *fd_stdout);
// int		exec_chain(t_chain *chain);

void	exec_sequence(t_array *sequence);
void	exec_external(t_command *cmd);
int		exec_builtin(t_command *command);

void	dup_std_start(int *fd_stdin, int *fd_stdout);
void	dup_std_end(int *fd_stdin, int *fd_stdout);

int		parse_input(char *str, t_array *sequence);
int		read_input(char **str);

void	run_child(t_command *cmd, int input, int ports[2], int last);
void	run_parent(t_command *cmd, int *fd, int ports[2]);
int		run_builtin_in_main(t_command *cmd);

int		super_duper(int fd_src, int fd_dst);
int		redirect(t_command *cmd, int input, int ports[2], int last);

int		cmd_is_external(t_command *cmd);
int		is_local_script(char *cmd);

#endif
