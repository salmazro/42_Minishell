/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:56:45 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void	read_argv(char **cursor);

int		readword_size(char *cursor, char *quote, t_env *env);

int		write_argv(char **cursor, char **argv, t_env *env);

int		get_argc(char *cursor);

int		set_argv(char *cursor, char **argv, t_env *env);

t_cmd	*parse_execmd(char **cursor, t_env *env);

t_cmd	*new_execmd(int argc, t_env *env);

t_cmd	*parser(char *cursor, t_env *env);

t_cmd	*parse_pipe(char **cursor, t_env *env);

t_cmd	*new_pipecmd(t_cmd *left, t_cmd *right);

t_cmd	*parse_redircmd(t_cmd *cmd, char **cursor, t_env *env);

t_cmd	*new_redircmd(t_cmd *subcmd, int mode, int fd, char *file);

int		get_token(char **cursor);

int		peek(char **cursor, char *toks);

char	*parsekey(char *q);

t_kms	*parsekeymap(char **q, t_env *env);

int		expandsize(char **ps, int in_quote, t_env *env);

int		expandline(char **ps, char **argv, t_env *env);

t_cmd	*move_cursor(t_cmd *cmd, char **cursor, t_env *env);

char	*expansion(char *ps, t_env *env);

int		readpureword_size(char *cursor);

void	checkheredoc_status(int stat, int fd);

#endif
