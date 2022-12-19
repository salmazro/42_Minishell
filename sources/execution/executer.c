/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:57:59 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

pid_t	child_pipe(t_cmd *cmd, int fd, int infd, int outfd)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		close(infd);
		dup2(outfd, fd);
		close(outfd);
		runcmd(cmd);
		exit(0);
	}
	return (pid);
}

int	runpipe(t_pipecmd *cmd)
{
	int		fd[2];
	pid_t	pid[2];
	int		stat;

	if (pipe(fd) < 0)
		print_error("pipe error");
	pid[0] = child_pipe(cmd->left, STDOUT_FILENO, fd[0], fd[1]);
	pid[1] = child_pipe(cmd->right, STDIN_FILENO, fd[1], fd[0]);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &stat, 0);
	if (WEXITSTATUS(stat))
		g_appinfo.exit_status = WEXITSTATUS(stat);
	return (0);
}

void	child_redircmd(t_redircmd *rcmd)
{
	int		fd_redirect;

	if (ft_strequals(rcmd->file, ".") && rcmd->fd > 2)
	{
		if (g_appinfo.pipe_out == -1)
			exit_app(g_appinfo.exit_status);
		dup2(rcmd->fd, STDIN_FILENO);
		close(rcmd->fd);
		runcmd(rcmd->subcmd);
		exit_app(g_appinfo.exit_status);
	}
	close(rcmd->fd);
	fd_redirect = open(rcmd->file, rcmd->mode, 0666);
	if (fd_redirect < 0)
	{
		if (errno == 13)
			ft_fprintf(2, "%s: Permission denied\n", rcmd->file);
		else
			ft_fprintf(2, "%s: No such file or directory\n", rcmd->file);
		exit_app(1);
	}
	runcmd(rcmd->subcmd);
	exit_app(g_appinfo.exit_status);
}

int	runredir(t_redircmd *cmd)
{
	t_redircmd	*rcmd;
	int			p_id;
	int			stat;

	rcmd = (t_redircmd *)cmd;
	p_id = ft_fork();
	if (p_id == 0)
		child_redircmd(rcmd);
	if (rcmd->fd > 2)
		close(rcmd->fd);
	waitpid(p_id, &stat, 0);
	if (WEXITSTATUS(stat))
		g_appinfo.exit_status = WEXITSTATUS(stat);
	return (0);
}
