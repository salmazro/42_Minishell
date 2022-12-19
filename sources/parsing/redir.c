/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:43 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	heredoc(char *delim, t_env *env, int fd_pipe)
{
	char		*buf;
	char		*temp;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		temp = expansion(buf, env);
		if (ft_strequals(temp, delim))
		{
			free(buf);
			free(temp);
			break ;
		}
		ft_fprintf(fd_pipe, "%s\n", temp);
		free(buf);
		free(temp);
	}
	close(fd_pipe);
	free(delim);
}

static void	child_heredoc(t_cmd *subcmd, char *delim, t_env *env, int pipe[2])
{
	signal(SIGINT, &sig_handler_heredoc);
	g_appinfo.cmd = subcmd;
	g_appinfo.pipe_in = pipe[1];
	g_appinfo.delim = delim;
	heredoc(delim, env, pipe[1]);
	close(pipe[0]);
}

t_cmd	*heredoccmd(t_cmd *subcmd, char *file, char *delim, t_env *env)
{
	int	p_id;
	int	stat;
	int	fd_pipe[2];

	if (pipe(fd_pipe) < 0)
		print_error("pipe");
	if (g_appinfo.pipe_out >= 0)
		close(g_appinfo.pipe_out);
	g_appinfo.pipe_out = fd_pipe[0];
	p_id = ft_fork();
	if (p_id == 0)
	{
		free(file);
		child_heredoc(subcmd, delim, env, fd_pipe);
		exit_app(0);
	}
	free(delim);
	close(fd_pipe[1]);
	waitpid(p_id, &stat, 0);
	checkheredoc_status(stat, fd_pipe[0]);
	return (new_redircmd(subcmd, O_RDONLY, fd_pipe[0], file));
}

t_cmd	*parse_redircmd(t_cmd *cmd, char **cursor, t_env *env)
{
	int		token;
	char	*file;

	if (cmd == NULL || peek(cursor, "|") || !**cursor)
		return (cmd);
	if (peek(cursor, "<>"))
	{
		token = get_token(cursor);
		if (get_token(cursor) != 'a')
			return (ft_fprintf(1, "syntax error\n"), NULL);
		write_argv(cursor, &file, env);
		if (token == '-')
			cmd = heredoccmd(cmd, ft_strdup("."), file, env);
		cmd = parse_redircmd(cmd, cursor, env);
		if (token == '<')
			cmd = new_redircmd(cmd, O_RDONLY, 0, file);
		else if (token == '>')
			cmd = new_redircmd(cmd, O_WRONLY | O_CREAT | O_TRUNC, 1, file);
		else if (token == '+')
			cmd = new_redircmd(cmd, O_WRONLY | O_CREAT | O_APPEND, 1, file);
	}
	else
		cmd = move_cursor(cmd, cursor, env);
	return (cmd);
}

t_cmd	*new_redircmd(t_cmd *subcmd, int mode, int fd, char *file)
{
	t_redircmd	*redircmd;

	redircmd = malloc(sizeof(t_redircmd));
	if (redircmd == NULL)
		exit(1);
	redircmd->type = REDIR;
	redircmd->subcmd = subcmd;
	redircmd->mode = mode;
	redircmd->fd = fd;
	redircmd->file = file;
	return ((t_cmd *)redircmd);
}
