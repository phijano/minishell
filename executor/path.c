/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:14:53 by phijano-          #+#    #+#             */
/*   Updated: 2022/09/26 12:59:12 by phijano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_memory_error(void *pnt)
{
	if (!pnt)
	{
		perror("Error\n");
		exit(1);
	}
}

int static	ft_has_path(char *cmd)
{
	int	count;
	int	bar;
	int	no_path;

	bar = 0;
	no_path = 0;
	count = -1;
	while (cmd[++count])
	{
		if (cmd[count] == '\"' || cmd[count] == '\'' || cmd[count] == ' ')
			no_path = 1;
		if (cmd[count] == '/' && no_path == 0)
			bar = 1;
	}
	return (bar);
}

char static	**ft_fix_path(char *full_path)
{
	char	**path;
	char	*temp;
	int		count;

	path = ft_split(full_path, ':');
	ft_check_memory_error(path);
	count = -1;
	while (path[++count])
	{
		temp = path[count];
		path[count] = ft_strjoin(path[count], "/");
		ft_check_memory_error(path[count]);
		free(temp);
	}
	return (path);
}

char static	*ft_get_env_path(char **envp)
{
	int		bar;
	int		c;
	char	*full_path;

	full_path = NULL;
	bar = 0;
	c = -1;
	while (envp[++c])
	{
		if (ft_strncmp(envp[c], "PATH", 4) == 0)
		{
			full_path = ft_substr(envp[c], 5, ft_strlen(envp[c]) - 5);
			ft_check_memory_error(full_path);
		}
	}
	bar = ft_has_path(full_path);
	if (bar == 0)
	{
		free(full_path);
		full_path = ft_strdup(".");
	}
	return (full_path);
}

char	**ft_get_path(char **envp)
{
	char	*full_path;
	char	**path;

	path = NULL;
	if (envp[0])
	{
		full_path = ft_get_env_path(envp);
	}
	else
	{
		full_path = ft_substr(PTH, 5, ft_strlen(PTH) - 5);
		ft_check_memory_error(full_path);
	}
	path = ft_fix_path(full_path);
	free(full_path);
	return (path);
}
