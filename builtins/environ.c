/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:19:22 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/26 16:48:40 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env[i])
		ft_putendl_fd(env[i++], 1);
	return (0);
}