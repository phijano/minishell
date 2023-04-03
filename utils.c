/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:55:53 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/23 12:08:03 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_env;

char	*ms_getenv(const char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], name, len) && g_env[i][len] == '=')
			return (&g_env[i][len + 1]);
		i++;
	}
	return (NULL);
}

int	envupdate(char *var, const char *newval)
{
	char	*tmp;
	int		varlen;
	int		vallen;

	varlen = ft_strlen(var);
	vallen = ft_strlen(newval);
	tmp = ft_calloc(varlen + vallen + 2, sizeof(char));
	if (!tmp || !newval)
	{
		free(tmp);
		perror("Error");
		return (1);
	}
	ft_strlcpy(tmp, var, varlen + 1);
	tmp[varlen] = '=';
	ft_strlcpy(&tmp[varlen + 1], newval, vallen + 1);
	vallen = 0;
	while (g_env[vallen] && !(!ft_strncmp(g_env[vallen], var, varlen)
			&& g_env[vallen][varlen] == '='))
		vallen++;
	free(g_env[vallen]);
	g_env[vallen] = tmp;
	return (0);
}

void	*free_cmndline(char **cmndline)
{
	int	i;

	i = 0;
	if (!cmndline)
		return (NULL);
	while (cmndline[i])
		free(cmndline[i++]);
	free(cmndline);
	return (NULL);
}

void	free_tables(t_parsing *cts)
{
	int	i;

	i = 0;
	if (!cts)
		return ;
	while (!cts[i].islast)
	{
		free_cmndline(cts[i].cmndtable);
		free_cmndline(cts[i].ins);
		free_cmndline(cts[i].outs);
		free(cts[i].iflgs);
		free(cts[i].oflgs);
		i++;
	}
	free(cts);
}
