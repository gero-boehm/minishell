/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:37:08 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/24 19:59:44 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	builtin_cd(char *str);
void	builtin_echo(int n, char *str);
void	builtin_env(void);
void	builtin_exit(void);
void	builtin_export(const char *key, char *value);
void	builtin_pwd(void);
void	builtin_unset(const char *key);

#endif