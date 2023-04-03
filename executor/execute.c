/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:39:24 by phijano-          #+#    #+#             */
/*   Updated: 2022/09/26 13:01:17 by phijano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int static	ft_path_cmd(char **cmd, char **envp)
{
	int		cmd_exist;

	cmd_exist = 0;
	if (access(cmd[0], F_OK) != -1)
	{
		cmd_exist = 1;
		if (access(cmd[0], X_OK) == -1)
			exit(0);
		else if (execve(cmd[0], cmd, envp) == -1)
			exit(1);
	}
	return (cmd_exist);
}

void static	ft_do_cmd(char **path, char **cmd, char **envp)
{
	int		count;
	char	*path_cmd;
	int		cmd_exist;

	cmd_exist = ft_path_cmd(cmd, envp);
	count = -1;
	while (path[++count])
	{
		path_cmd = ft_strjoin(path[count], cmd[0]);
		ft_check_memory_error(path_cmd);
		if (access(path_cmd, F_OK) != -1)
		{
			cmd_exist = 1;
			if (execve(path_cmd, cmd, envp) == -1)
				exit(1);
		}
		free(path_cmd);
	}
	if (cmd_exist == 0)
		exit(127);
}

void	ft_execute(t_process process, char **cmd, char **envp)
{
	char	**path;

	if (process.in_fd_pipex[1] >= 0 && process.in_fd_pipex[1]
		!= process.fd_in && process.in_fd_pipex[1] != process.fd_out)
		close(process.in_fd_pipex[1]);
	if (process.out_fd_pipex[0] >= 0 && process.out_fd_pipex[0]
		!= process.fd_in && process.out_fd_pipex[0] != process.fd_out)
		close(process.out_fd_pipex[0]);
	dup2(process.fd_in, 0);
	close(process.fd_in);
	dup2(process.fd_out, 1);
	close(process.fd_out);
	path = ft_get_path(envp);
	if (process.fd_in < 0 || process.fd_out < 0)
		exit(1);
	ft_do_cmd(path, cmd, envp);
	free(path);
}
