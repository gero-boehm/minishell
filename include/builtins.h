/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:37:08 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 16:07:46 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	builtin_cd(char *str);
int	builtin_echo(int n, char *str);
int	builtin_env(void);
int	builtin_exit(void);
int	builtin_export(void);
int	builtin_pwd(void);
int	builtin_unset(void);

#endif