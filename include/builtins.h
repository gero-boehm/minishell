/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:37:08 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/26 16:30:02 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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