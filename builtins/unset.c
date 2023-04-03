/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:48:48 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/26 16:48:58 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	envrem(const char *var, char **env)
{
	int	i;
	int	len;

	if (!var)
		return (1);
	i = 0;
	len = ft_strlen(var);
	while (env[i] && !(!ft_strncmp(env[i], var, len) && env[i][len] == '='))
		i++;
	free(env[i]);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	return (0);
}

int	ms_unset(const char **vars, char **env)
{
	if (!vars || !*vars)
		return (1);
	vars++;
	while (*vars)
	{
		if (envrem(*vars, env))
			return (1);
		vars++;
	}
	return (0);
}
