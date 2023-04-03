/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:14:56 by phijano-          #+#    #+#             */
/*   Updated: 2022/09/26 13:48:27 by phijano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_fd_in(t_process *process, char **ins, int *iflgs)
{
	int	count;

	if (process->out_fd_pipex[0] >= 0)
	{
		process->in_fd_pipex[0] = process->out_fd_pipex[0];
		process->in_fd_pipex[1] = process->out_fd_pipex[1];
		process->fd_in = process->in_fd_pipex[0];
	}
	count = -1;
	if (!ins)
		return ;
	while (ins[++count])
	{
		if (count > 0)
			close(process->fd_in);
		if (iflgs[count])
		{
			process->here_doc++;
			dochere(process, ins[count]);
		}
		else
			process->fd_in = open(ins[count], O_RDONLY);
		if (process->fd_in == -1)
			break ;
	}
}

void	ft_set_fd_out(t_process *process, char **outs, int *oflgs)
{
	int	count;

	pipe(process->out_fd_pipex);
	process->fd_out = process->out_fd_pipex[1];
	if (!outs)
		return ;
	count = -1;
	while (outs[++count])
	{
		if (count > 0)
			close(process->fd_out);
		if (oflgs[count])
			process->fd_out = open(outs[count], O_CREAT
					| O_RDWR | O_APPEND, 0644);
		else
			process->fd_out = open(outs[count], O_WRONLY | O_CREAT
					| O_TRUNC | O_APPEND, S_IRWXU);
		if (process->fd_out == -1)
			break ;
	}
}

void	ft_close_fds(t_process process)
{
	if (process.fd_in >= 0)
		close(process.fd_in);
	if (process.fd_out >= 0 && process.fd_out)
		close(process.fd_out);
	if (process.in_fd_pipex[0] >= 0 && process.in_fd_pipex[0] != process.fd_in)
		close(process.in_fd_pipex[0]);
	if (process.out_fd_pipex[1] >= 0 && process.out_fd_pipex[1]
		!= process.fd_out && process.out_fd_pipex[1] != process.in_fd_pipex[1])
		close(process.out_fd_pipex[1]);
}
