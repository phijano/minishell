/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:57:51 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/26 16:53:12 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/ioctl.h>

# define PTH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"

// Parser stuff.

typedef struct s_parsing
{
	char	**cmndtable;
	char	**ins;
	int		*iflgs;
	char	**outs;
	int		*oflgs;
	int		islast;
}	t_parsing;

t_parsing	*parse_line(char *line);
char		**tokenize_line(char *line);

// Utils.
char		*ms_getenv(const char *name);
int			envupdate(char *var, const char *newval);
void		*free_cmndline(char **cmndline);
void		free_tables(t_parsing *cts);

// Builtins.

int			ms_echo(t_parsing cts);
int			ms_pwd(void);
int			ms_cd(const char **cmndarr);
int			ms_export(const char **vars, char ***env);
int			ms_unset(const char **vars, char **env);
int			ms_env(char **env);
int			ms_exit(t_parsing *cts, char *cmndline, char *prompt);

// Executor.

typedef struct s_process
{
	int	fd_in;
	int	fd_out;
	int	pid;
	int	in_fd_pipex[2];
	int	out_fd_pipex[2];
	int	here_doc;
	int	last_process;
	int	exit_code;
}	t_process;

void		ft_executor(t_parsing *task, char **envp);
void		ft_set_fd_in(t_process *process, char **ins, int *iflgs);
void		ft_set_fd_out(t_process *process, char **outs, int *oflgs);
void		dochere(t_process *process, char *limit);
void		ft_close_fds(t_process process);
void		ft_remove_here(int count);
void		ft_check_cmds(t_parsing *task, char **envp);
int			ft_check_built(t_parsing task, t_process *process);
int			ft_fake_exit(t_parsing task);
void		ft_execute(t_process process, char **cmd, char **envp);
char		**ft_get_path(char **envp);
int			ft_exit_status(int status);
int			ft_exit_code(int status);
void		ft_check_memory_error(void *pnt);

// Signals.

void		ft_ctrl_c(int sig);

#endif
