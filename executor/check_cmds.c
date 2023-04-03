/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:09 by phijano-          #+#    #+#             */
/*   Updated: 2023/04/03 10:21:40 by phijano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void static	ft_arg_error(char *s, int error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	if (error == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}

void static	ft_check_cmd(char **path, char *cmd)
{
	int		count;
	int		exist;
	char	*path_cmd;

	count = -1;
	exist = 0;
	if (access(cmd, F_OK) != -1)
		exist = 1;
	while (path[++count] && exist == 0)
	{
		path_cmd = ft_strjoin(path[count], cmd);
		ft_check_memory_error(path_cmd);
		if (access(path_cmd, F_OK) != -1)
			exist = 1;
		free(path_cmd);
	}
	if (exist == 0)
		ft_arg_error(cmd, 1);
}

int static	ft_check_files(char **files, int ins_outs, int *iflgs)
{
	int	f1;
	int	count;
	int	error;

	error = 0;
	count = -1;
	while (files[++count])
	{
		if (ins_outs == 0)
		{
			if (!iflgs[count])
				f1 = open(files[count], O_RDONLY);
		}
		else
			f1 = open(files[count], O_CREAT | O_RDWR, 0644);
		if (f1 < 0)
		{
			ft_arg_error(files[count], 0);
			error = 1;
			break ;
		}
		if (f1 > 1)
			close(f1);
	}
	return (error);
}

void static	ft_check_exit_args(t_parsing task)
{
	if (ft_fake_exit(task))
	{
		ft_putstr_fd("minishell : exit: ", 1);
		ft_putstr_fd("too many arguments\n", 1);
	}
}

void	ft_check_cmds(t_parsing *task, char **envp)
{
	int		count;
	char	**path;

	count = -1;
	while (task[++count].cmndtable)
	{
		if (!ft_check_files(task[count].ins, 0, task[count].iflgs))
		{
			if (!ft_check_files(task[count].outs, 1, task[count].oflgs))
			{
				path = ft_get_path(envp);
				if (!ft_strncmp(task[count].cmndtable[0], "exit", 5))
					ft_check_exit_args(task[count]);
				else if (ft_strncmp(task[count].cmndtable[0], "export", 7)
					&& ft_strncmp(task[count].cmndtable[0], "unset", 6))
					ft_check_cmd(path, task[count].cmndtable[0]);
				free_cmndline(path);
			}
		}
	}
}
