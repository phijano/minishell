/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:56:41 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/27 16:54:18 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char	**g_env;

//
/** static void	leakcheck(void)
  * {
  *     system("leaks minishell");
  * } */
//

static int	numcheck(char *str)
{
	while (*str)
		if (!ft_isdigit(*(str++)))
			return (1);
	return (0);
}

int	ms_exit(t_parsing *cts, char *cmndline, char *prompt)
{
	int	exval;

	ft_putendl_fd("exit", 1);
	if (cts->cmndtable[1])
	{
		if (numcheck(cts->cmndtable[1]))
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (255);
		}
		if (cts->cmndtable[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		exval = ft_atoi(cts->cmndtable[1]);
	}
	else
		exval = ft_atoi(ms_getenv("?"));
	free(prompt);
	free(cmndline);
	free_cmndline(g_env);
	free_tables(cts);
	return (exval);
}
/** 
  *     //
  *     leakcheck(); RIGHT BEFORE RETURN.
  *     //
  *  */
