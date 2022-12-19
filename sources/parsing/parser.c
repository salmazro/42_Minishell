/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:28 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*move_cursor(t_cmd *cmd, char **cursor, t_env *env)
{
	int	token;

	token = get_token(cursor);
	if (token == 0)
		return (0);
	if (token == 'a')
		(*cursor) += readpureword_size(*cursor);
	return (parse_redircmd(cmd, cursor, env));
}

t_cmd	*parser(char *cursor, t_env *env)
{
	t_cmd	*cmd;

	if (!*cursor)
		return (0);
	cmd = parse_pipe(&cursor, env);
	return (cmd);
}

int	peek(char **cursor, char *toks)
{
	while (**cursor && ft_strchr(SPACES, **cursor))
		(*cursor)++;
	return (**cursor && ft_strchr(toks, **cursor));
}
