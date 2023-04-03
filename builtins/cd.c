/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:01:53 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/23 11:54:18 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_cd(const char **cmndarr)
{
	char	*path;

	if (!cmndarr[1])
		path = ms_getenv("HOME");
	else
		path = (char *)cmndarr[1];
	if (chdir(path) == -1)
	{
		perror("Error");
		return (1);
	}
	envupdate("OLDPWD", ms_getenv("PWD"));
	path = getcwd(NULL, 0);
	envupdate("PWD", path);
	free(path);
	return (0);
}
