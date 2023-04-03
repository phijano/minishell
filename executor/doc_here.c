/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:14:51 by phijano-          #+#    #+#             */
/*   Updated: 2022/09/26 14:17:50 by phijano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char static	*ft_get_file(t_process process)
{
	char	*file_here;
	char	*tmp;

	tmp = ft_itoa(process.here_doc);
	ft_check_memory_error(tmp);
	file_here = ft_strjoin(tmp, "_here_doc.tmp");
	free(tmp);
	ft_check_memory_error(file_here);
	return (file_here);
}

void	dochere(t_process *process, char *limit)
{
	char	temp[4096];
	int		readflag;
	char	*file_here;

	file_here = ft_get_file(*process);
	process->fd_in = open(file_here, O_CREAT | O_WRONLY | O_APPEND, 0644);
	readflag = 1;
	while (readflag)
	{
		ft_putstr_fd("minishell heredoc >", 1);
		readflag = read(0, temp, 4096);
		if (!ft_strncmp(limit, temp, ft_strlen(limit))
			&& temp[ft_strlen(limit)] == '\n')
			break ;
		write(process->fd_in, temp, readflag);
	}
	close(process->fd_in);
	process->fd_in = open(file_here, O_RDONLY);
	free(file_here);
	if (process->fd_in < 0)
		perror("Error: ");
}

void	ft_remove_here(int count)
{
	char	*file;
	char	*tmp;

	while (count > 0)
	{
		tmp = ft_itoa(count--);
		ft_check_memory_error(tmp);
		file = ft_strjoin(tmp, "_here_doc.tmp");
		ft_check_memory_error(file);
		free(tmp);
		unlink(file);
		free(file);
	}
}
