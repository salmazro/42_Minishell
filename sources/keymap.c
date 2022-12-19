/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:59:28 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*merge_keymap(t_kms *km)
{
	char	*ret;
	char	*temp;

	ret = ft_strjoin(km->key, "=");
	if (km->val != NULL)
	{
		temp = ret;
		ret = ft_strjoin(temp, km->val);
		free(temp);
	}
	return (ret);
}

void	update_keymap(t_kms *km, char *keyvalue)
{
	size_t		size;
	size_t		index;

	size = ft_strclen(keyvalue, '=') + 1;
	index = size;
	km->key = ft_strldup(keyvalue, size);
	if (index >= ft_strlen(keyvalue))
	{
		if (ft_strchr(keyvalue, '='))
			km->val = "";
		else
			km->val = NULL;
		return ;
	}
	size = ft_strlen(&keyvalue[index]) + 1;
	km->val = ft_strldup(&keyvalue[index], size);
}

t_list	*find_keymap_key(t_list *lst, char *keyvalue)
{
	t_list	*curr;
	size_t	size;
	char	*key;

	size = ft_strclen(keyvalue, '=') + 1;
	key = ft_strldup(keyvalue, size);
	curr = lst;
	while (curr && !ft_strequals(key, ((t_kms *)curr->content)->key))
		curr = curr->next;
	free(key);
	return (curr);
}

void	add_keymap(t_list **lst, char *keyvalue, int addonly)
{
	t_list	*curr;
	t_kms	*km;

	curr = find_keymap_key(lst[0], keyvalue);
	if (curr && !addonly)
	{
		km = (t_kms *)curr->content;
		free(km->key);
		if (km->val && *km->val)
			free(km->val);
		update_keymap(km, keyvalue);
	}
	else if (!curr)
	{
		km = malloc(sizeof(t_kms));
		if (!km)
			print_error("malloc error\n");
		update_keymap(km, keyvalue);
		ft_lstadd_back(lst, ft_lstnew(km));
	}
}

void	remove_keymap(t_list **lst, char *key)
{
	t_list	*curr;
	t_list	*last;
	t_list	*next;

	curr = lst[0];
	last = NULL;
	while (curr)
	{
		next = curr->next;
		if (ft_strequals(((t_kms *)curr->content)->key, key))
		{
			if (last)
				last->next = next;
			else
				lst[0] = next;
			clear_keymap(curr->content);
			free(curr);
			curr = NULL;
		}
		last = curr;
		curr = next;
	}
}
