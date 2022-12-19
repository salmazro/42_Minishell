/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:24 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*parsekey(char *q)
{
	int		i;
	char	*key;

	i = 0;
	if (q[i] && (ft_isdigit(q[i]) || q[i] == '?'))
		i++;
	else
	{
		while (q[i] && ft_isalnum(q[i]))
			i++;
		if (!i)
			return (NULL);
	}
	key = ft_strldup(q, i + 1);
	if (!key)
		print_error("malloc error\n");
	return (key);
}

t_kms	*parsekeymap(char **q, t_env *env)
{
	char	*key;
	t_list	*keyvalue;

	key = parsekey(*q);
	if (!key)
		return (0);
	*q += ft_strlen(key);
	keyvalue = find_keymap_key(env->kms, key);
	free(key);
	if (!keyvalue)
		return (0);
	return ((t_kms *)keyvalue->content);
}

int	expandsize(char **ps, int in_quote, t_env *env)
{
	t_kms	*km;

	(*ps)++;
	if (**ps && !ft_strchr(SPACES, **ps))
	{
		km = parsekeymap(ps, env);
		if (km)
			return (ft_strlen(km->val));
		return (in_quote);
	}
	return (1);
}

int	expandline(char **ps, char **argv, t_env *env)
{
	t_kms	*km;

	(*ps)++;
	if (**ps && !ft_strchr(SPACES, **ps))
	{
		km = parsekeymap(ps, env);
		if (km)
		{
			**argv = '\0';
			*argv += ft_strlcat(*argv, km->val, ft_strlen(km->val) + 1);
			return (0);
		}
		return (1);
	}
	**argv = *((*ps) - 1);
	(*argv)++;
	return (0);
}

char	*expansion(char *ps, t_env *env)
{
	char	*new;
	char	*new_temp;
	char	*s;
	size_t	len;

	len = ft_strlen(ps);
	new = ft_calloc(sizeof(char), (len + 1));
	if (!new)
		print_error("malloc error\n");
	s = ps;
	new_temp = new;
	while (*s)
	{
		if (*s == '$' && expandline(&s, &new_temp, env))
			continue ;
		*new_temp = *s;
		new_temp++;
		s++;
	}
	return (new);
}
