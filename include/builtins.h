/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:49:07 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:49:07 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "cmddef.h"

int	builtin_cd(t_builtin_cd *cd);
int	builtin_echo(t_builtin_echo	*echo);
int	builtin_env(void);
int	builtin_exit(t_builtin_exit *data);
int	builtin_export(t_builtin_export	*export);
int	builtin_pwd(void);
int	builtin_unset(t_builtin_unset *unset);

#endif