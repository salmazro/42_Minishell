/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:57:24 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

void	check_cmddir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return ;
		i++;
	}
	ft_fprintf(2, "%s: command not found\n", cmd);
	exit_app(127);
}

static void	error(char *cmd)
{
	int			fstatus;
	struct stat	buff;

	if (errno == 8)
		exit_app(0);
	fstatus = stat(cmd, &buff);
	check_cmddir(cmd);
	if (!fstatus)
	{
		if (buff.st_mode & S_IFDIR)
			ft_fprintf(2, "%s: is a directory\n", cmd);
		else
		{
			ft_fprintf(2, "%s: ", cmd);
			perror(NULL);
		}
		exit_app(126);
	}
	ft_fprintf(2, "%s: ", cmd);
	perror(NULL);
	exit_app(127);
}

void	ft_execve(char *cmd, char **argv, t_env *env)
{
	char		*path;
	pid_t		p_id;
	int			status;

	update_env(env);
	p_id = ft_fork();
	if (p_id == 0)
	{
		path = full_command_path(cmd, env->env);
		execve(path, argv, env->env);
		error(cmd);
	}
	waitpid(p_id, &status, 0);
	if (WEXITSTATUS(status))
		g_appinfo.exit_status = WEXITSTATUS(status);
}
