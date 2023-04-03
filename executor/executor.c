/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:31:55 by phijano-          #+#    #+#             */
/*   Updated: 2023/04/03 10:35:11 by phijano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void static	ft_init_process(t_process *process)
{
	process->here_doc = 0;
	process->in_fd_pipex[0] = -1;
	process->in_fd_pipex[1] = -1;
	process->out_fd_pipex[0] = -1;
	process->out_fd_pipex[1] = -1;
	process->last_process = -1;
	process->exit_code = -1;
}

void static	ft_fork(t_process *process, t_parsing task, char **envp)
{
	process->pid = fork();
	if (process->pid == -1)
		perror("Error fork\n");
	else if (process->pid == 0)
		ft_execute(*process, task.cmndtable, envp);
	else
		ft_close_fds(*process);
}

void static	ft_father(t_process process)
{
	int		status;
	char	*exit_code;

	if (process.out_fd_pipex[0] >= 0)
		close(process.out_fd_pipex[0]);
	if (process.here_doc > 0)
		ft_remove_here(process.here_doc);
	waitpid(process.pid, &status, 0);
	exit_code = NULL;
	if (process.last_process)
		exit_code = ft_itoa(process.exit_code);
	else if (ft_exit_status(status))
		exit_code = ft_itoa(ft_exit_code(status));
	envupdate("?", exit_code);
	free(exit_code);
}

void	ft_executor(t_parsing *task, char **envp)
{
	t_process	process;
	int			count;

	if (!task || !task[0].cmndtable || !task[0].cmndtable[0])
		return ;
	ft_check_cmds(task, envp);
	ft_init_process(&process);
	count = -1;
	while (task[++count].cmndtable)
	{
		if (count == 0 && task[count].ins[0] == NULL)
			process.fd_in = dup(0);
		else
			ft_set_fd_in(&process, task[count].ins, task[count].iflgs);
		if (!task[count + 1].cmndtable && task[count].outs[0] == NULL)
			process.fd_out = dup(1);
		else
			ft_set_fd_out(&process, task[count].outs, task[count].oflgs);
		process.last_process = ft_check_built(task[count], &process);
		if (!process.last_process)
			ft_fork(&process, task[count], envp);
	}
	ft_father(process);
}
