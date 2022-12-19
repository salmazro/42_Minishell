/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:56:36 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

int			runexec(t_execmd *cmd);

pid_t		child_pipe(t_cmd *cmd, int fd, int infd, int outfd);

int			runpipe(t_pipecmd *cmd);

int			runredir(t_redircmd *cmd);

int			runcmd(t_cmd *cmd);

int			ft_chdir(char *path);

void		ft_cd(char **argv, t_env *env);

void		ft_echo(char **argv);

void		ft_env(t_env *env);

void		check_cmddir(char *cmd);

void		ft_execve(char *cmd, char **argv, t_env *env);

long long	ft_atoull(char *str);

void		ft_exit(char **argv, t_env *env);

void		ft_export(char **argv, t_env *env);

char		*ft_get_pwd(void);

void		ft_pwd(void);

void		ft_update_pwd(char *key, t_env *env);

void		ft_unset(char **argv, t_env *env);

int			len_ch(char *str, char ch);

int			ncompare(char *str1, char *str2, int n);

char		*make_command(char *path, char *bin);

char		*str_ndup(char *str, unsigned int n);

char		*full_command_path(char *cmd, char **env);

#endif
