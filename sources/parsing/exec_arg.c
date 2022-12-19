/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:17 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	read_argv(char **cursor)
{
	while (**cursor && !ft_strchr(SPACES, **cursor)
		&&!ft_strchr(SYMBOLS, **cursor))
	{
		(*cursor)++;
	}
}

int	get_argc(char *cursor)
{
	int	token;
	int	argc;

	argc = 0;
	while (!peek(&cursor, "|"))
	{
		token = get_token(&cursor);
		if (token == 0)
			break ;
		if (ft_strchr("+-<>", token))
		{
			read_argv(&cursor);
			continue ;
		}
		if (token != 'a')
			print_error("syntax");
		read_argv(&cursor);
		argc++;
	}
	return (argc);
}

int	set_argv(char *cursor, char **argv, t_env *env)
{
	int	token;
	int	argc;

	argc = 0;
	while (!peek(&cursor, "|"))
	{
		token = get_token(&cursor);
		if (token == 0)
			break ;
		if (ft_strchr("+-<>", token))
		{
			read_argv(&cursor);
			continue ;
		}
		if (token != 'a')
			print_error("syntax");
		if (write_argv(&cursor, &argv[argc], env))
			return (1);
		argc++;
	}
	argv[argc] = 0;
	return (0);
}
