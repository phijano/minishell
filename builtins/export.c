/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:47:45 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/26 16:54:04 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**envadd(const char *var, char **env)
{
	int		len;
	int		i;
	char	**tmp;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	tmp = ft_calloc(len-- + 2, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i] = ft_strdup(var);
	if (!tmp[i++])
	{
		free(tmp);
		return (NULL);
	}
	tmp[i] = env[len];
	return (tmp);
}

static int	ms_export_one(const char *var, char ***env)
{
	char	**tmp;
	char	*equalpos;

	equalpos = ft_strchr(var, '=');
	if (!equalpos)
	{
		ft_putendl_fd("Error: Exported var must have a value assigned.", 2);
		return (1);
	}
	*equalpos = 0;
	if (ms_getenv(var))
	{
		envupdate((char *)var, &equalpos[1]);
		return (0);
	}
	*equalpos = '=';
	tmp = envadd(var, *env);
	if (!tmp)
	{
		perror("Error");
		return (1);
	}
	free(*env);
	*env = tmp;
	return (0);
}

int	ms_export(const char **vars, char ***env)
{
	int	i;

	i = 1;
	while (vars[i])
		if (ms_export_one(vars[i++], env))
			return (1);
	return (0);
}
