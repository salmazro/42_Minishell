/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:52 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"parser.h"

int	redirtoken(char **cursor)
{
	int	token;

	token = **cursor;
	if (**cursor == '>')
	{
		(*cursor)++;
		if (**cursor == '>')
		{
			(*cursor)++;
			token = '+';
		}
	}
	else if (**cursor == '<')
	{
		(*cursor)++;
		if (**cursor == '<')
		{
			(*cursor)++;
			token = '-';
		}
	}
	return (token);
}

int	get_token(char **cursor)
{
	int	token;

	while (**cursor && ft_strchr(SPACES, **cursor))
		(*cursor)++;
	token = **cursor;
	if (**cursor == '|')
		(*cursor)++;
	else if (**cursor == '>' || **cursor == '<')
		token = redirtoken(cursor);
	else if (**cursor)
		token = 'a';
	while (**cursor && ft_strchr(SPACES, **cursor))
		(*cursor)++;
	return (token);
}
