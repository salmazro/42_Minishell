/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:38 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	checkquote(char **cursor, char *quote, int *in_quote)
{
	if (!*in_quote && ft_strchr(QUOTES, **cursor))
		*quote = **cursor;
	if (**cursor == *quote)
	{
		*in_quote = !(*in_quote);
		(*cursor)++;
		return (1);
	}
	if (!*in_quote && (ft_strchr(SPACES, **cursor)
			|| ft_strchr(SYMBOLS, **cursor)))
		return (-1);
	return (0);
}

int	readpureword_size(char *cursor)
{
	int	len;

	len = 0;
	while (*cursor && !ft_strchr(SPACES, *cursor)
		&& !ft_strchr(SYMBOLS, *cursor))
	{
		len++;
		cursor++;
	}
	return (len);
}

int	readword_size(char *cursor, char *q, t_env *env)
{
	int	len;
	int	iq;
	int	status;

	len = 0;
	iq = 0;
	status = 0;
	while (*cursor)
	{
		status = checkquote(&cursor, q, &iq);
		if (status == 1)
			continue ;
		if (status == -1)
			break ;
		if ((iq && *q != '\'' && *cursor == '$') || (!iq && *cursor == '$'))
		{
			len += expandsize(&cursor, iq, env);
			continue ;
		}
		len++;
		cursor++;
	}
	if (iq)
		return (-1);
	return (len);
}

void	writeword(char **cursor, char **argv, char *q, t_env *env)
{
	char	*str;
	int		iq;
	int		status;

	iq = 0;
	status = 0;
	str = *argv;
	while (**cursor)
	{
		status = checkquote(cursor, q, &iq);
		if (status == 1)
			continue ;
		if (status == -1)
			break ;
		if ((iq && *q != '\'' && **cursor == '$') || (!iq && **cursor == '$'))
		{
			if (!expandline(cursor, &str, env) || !iq)
				continue ;
			(*cursor)--;
		}
		*str = **cursor;
		str++;
		(*cursor)++;
	}
	*str = '\0';
}

int	write_argv(char **cursor, char **argv, t_env *env)
{
	int		len;
	char	quote;

	quote = '\0';
	len = readword_size(*cursor, &quote, env);
	if (len < 0)
	{
		ft_fprintf(2, "syntax - missing %c\n", quote);
		return (1);
	}
	*argv = malloc(sizeof(char) * (len + 1));
	if (*argv == NULL)
		return (0);
	writeword(cursor, argv, &quote, env);
	return (0);
}
