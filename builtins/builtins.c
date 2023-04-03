/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:06:32 by phijano-          #+#    #+#             */
/*   Updated: 2022/09/26 16:55:09 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char extern	**g_env;

int	ft_fake_exit(t_parsing task)
{
	int	count;

	count = 0;
	while (task.cmndtable[++count])
		if (count > 1)
			return (1);
	return (0);
}

int static	ft_builtins(t_parsing task)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strncmp(task.cmndtable[0], "echo", 5))
		exit_code = ms_echo(task);
	else if (!ft_strncmp(task.cmndtable[0], "cd", 3))
		exit_code = ms_cd((const char **)task.cmndtable);
	else if (!ft_strncmp(task.cmndtable[0], "pwd", 4))
		exit_code = ms_pwd();
	else if (!ft_strncmp(task.cmndtable[0], "export", 7))
		exit_code = ms_export((const char **)task.cmndtable, &g_env);
	else if (!ft_strncmp(task.cmndtable[0], "unset", 6))
		exit_code = ms_unset((const char **)task.cmndtable, g_env);
	else if (!ft_strncmp(task.cmndtable[0], "env", 4))
		exit_code = ms_env(g_env);
	else if (!ft_strncmp(task.cmndtable[0], "exit", 5))
		exit_code = ft_fake_exit(task);
	return (exit_code);
}

void static	ft_set_in_out(t_process process)
{
	dup2(process.fd_in, 0);
	dup2(process.fd_out, 1);
	close(process.fd_in);
	close(process.fd_out);
}

int	ft_check_built(t_parsing task, t_process *process)
{
	int	built;
	int	tmp_stdin;
	int	tmp_stdout;

	built = 1;
	if (!ft_strncmp(task.cmndtable[0], "echo", 5)
		|| !ft_strncmp(task.cmndtable[0], "cd", 3)
		|| !ft_strncmp(task.cmndtable[0], "pwd", 4)
		|| !ft_strncmp(task.cmndtable[0], "export", 7)
		|| !ft_strncmp(task.cmndtable[0], "unset", 6)
		|| !ft_strncmp(task.cmndtable[0], "env", 4)
		|| !ft_strncmp(task.cmndtable[0], "exit", 5))
	{
		tmp_stdin = dup(0);
		tmp_stdout = dup(1);
		ft_set_in_out(*process);
		process->exit_code = ft_builtins(task);
		dup2(tmp_stdin, 0);
		dup2(tmp_stdout, 1);
	}
	else
		built = 0;
	return (built);
}
