/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:08 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"
#include "parser.h"

int	runcmd(t_cmd *cmd)
{
	int	status;

	status = 1;
	if (cmd == NULL)
		return (0);
	if (cmd->type == EXEC)
	{
		status = runexec((t_execmd *)cmd);
	}
	else if (cmd->type == REDIR)
	{
		status = runredir((t_redircmd *)cmd);
	}
	else if (cmd->type == PIPE)
	{
		status = runpipe((t_pipecmd *)cmd);
	}
	return (status);
}

int	runexec(t_execmd *cmd)
{
	define_exec_signals();
	if (ft_strequals(cmd->argv[0], "exit"))
	{
		ft_exit(cmd->argv, cmd->env);
		return (0);
	}
	g_appinfo.exit_status = 0;
	if (ft_strequals(cmd->argv[0], "cd"))
		ft_cd(cmd->argv, cmd->env);
	else if (ft_strequals(cmd->argv[0], "env"))
		print_env(cmd->env->kms);
	else if (ft_strequals(cmd->argv[0], "pwd"))
		ft_pwd();
	else if (ft_strequals(cmd->argv[0], "echo"))
		ft_echo(cmd->argv);
	else if (ft_strequals(cmd->argv[0], "export"))
		ft_export(cmd->argv, cmd->env);
	else if (ft_strequals(cmd->argv[0], "unset"))
		ft_unset(cmd->argv, cmd->env);
	else
		ft_execve(cmd->argv[0], cmd->argv, cmd->env);
	return (0);
}
