/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:48:58 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/22 15:48:59 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

int	env_init(void);
int	env_get(const char *key, char **value);
int	env_set(const char *key, char *value);
int	env_remove(const char *key);
int	env_get_all(char ***arr);

#endif