/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:37:08 by cmeng             #+#    #+#             */
/*   Updated: 2023/07/20 15:03:59 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	cd(char *str);
int	echo(int n, char *str);
int	env(void);
// int	exit(void);
int	export(void);
int	pwd(void);
int	unset(void);

#endif