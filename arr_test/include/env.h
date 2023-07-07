/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:29:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/07 18:03:01 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

int	env_init(char **envp);
int	env_get(const char *key, char **value);
int	env_set(const char *key, char *value);
int	env_remove(const char *key);
int	env_get_all(char ***arr);

#endif