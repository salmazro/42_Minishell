/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:33 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parse_pipe(char **cursor, t_env *env)
{
	t_cmd	*cmd;

	cmd = parse_execmd(cursor, env);
	if (peek(cursor, "|"))
	{
		get_token(cursor);
		cmd = new_pipecmd(cmd, parse_pipe(cursor, env));
	}
	return (cmd);
}

t_cmd	*new_pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*pipecmd;

	pipecmd = malloc(sizeof(t_pipecmd));
	if (pipecmd == NULL)
		exit(1);
	pipecmd->type = PIPE;
	pipecmd->left = left;
	pipecmd->right = right;
	return ((t_cmd *)pipecmd);
}
