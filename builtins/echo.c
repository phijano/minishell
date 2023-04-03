/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:48:18 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/19 12:05:45 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_echo(t_parsing cts)
{
	int	i;
	int	nflag;

	i = 1;
	nflag = 0;
	if (cts.cmndtable[i] && !ft_strncmp(cts.cmndtable[i], "-n", 3))
	{
		i++;
		nflag++;
	}
	while (cts.cmndtable[i])
	{
		ft_putstr_fd(cts.cmndtable[i], 1);
		if (cts.cmndtable[++i])
			write(1, " ", 1);
	}
	if (!nflag)
		write(1, "\n", 1);
	return (0);
}
