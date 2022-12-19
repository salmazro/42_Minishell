/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:59:25 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env(int size)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		print_error("malloc error\n");
	new->kms = NULL;
	new->env = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new->env)
		print_error("malloc error\n");
	return (new);
}

static void	update_shellvl(t_env *new)
{
	t_list	*curr;
	t_kms	*km;
	char	*temp;
	char	*temp2;
	int		value;

	curr = find_keymap_key(new->kms, "SHLVL");
	if (curr)
	{
		km = (t_kms *)curr->content;
		value = ft_atoi(km->val);
		if (value >= 0)
		{
			temp = ft_itoa(value + 1);
			temp2 = ft_strjoin("SHLVL=", temp);
			free(temp);
			add_keymap(&new->kms, temp2, 0);
			free(temp2);
			return ;
		}
	}
	add_keymap(&new->kms, "SHLVL=1", 0);
}

t_env	*init_env(char **env)
{
	size_t	i;
	size_t	size;
	t_env	*new;
	t_kms	*km;

	size = ft_strdlen(env);
	new = new_env(size);
	i = 0;
	while (i < size)
	{
		km = malloc(sizeof(t_kms));
		if (!km)
			print_error("malloc error\n");
		update_keymap(km, env[i]);
		new->env[i] = ft_strdup(env[i]);
		ft_lstadd_back(&new->kms, ft_lstnew(km));
		i++;
	}
	new->env[i] = ft_strdup("?=0");
	add_keymap(&new->kms, new->env[i], 0);
	new->env[++i] = 0;
	add_keymap(&new->kms, "OLDPWD", 1);
	update_shellvl(new);
	return (new);
}

char	**ft_getenv(t_list *lst)
{
	t_list	*curr;
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!ret)
		print_error("malloc error\n");
	curr = lst;
	i = 0;
	while (curr)
	{
		ret[i++] = merge_keymap((t_kms *)curr->content);
		curr = curr->next;
	}
	ret[i] = 0;
	return (ret);
}

void	update_env(t_env *env)
{
	ft_clearsplit(env->env);
	env->env = ft_getenv(env->kms);
}
