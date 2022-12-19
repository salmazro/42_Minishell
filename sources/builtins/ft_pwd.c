/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:57:39 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
{
	char	*buff;

	buff = NULL;
	return (getcwd(buff, 0));
}

void	ft_pwd(void)
{
	char	*pwd;
	t_list	*curr;

	pwd = ft_get_pwd();
	if (pwd)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		curr = find_keymap_key(g_appinfo.env->kms, "PWD");
		if (curr)
			ft_printf("%s\n", ((t_kms *)curr->content)->val);
		else
			ft_printf("error: can't find PWD\n");
	}
}

void	ft_update_pwd(char *key, t_env *env)
{
	t_list	*curr;
	char	*keyvalue;
	char	*keytemp;
	char	*pwdtemp;

	keyvalue = NULL;
	curr = find_keymap_key(env->kms, key);
	if (curr)
	{
		keytemp = ft_strjoin(key, "=");
		pwdtemp = ft_get_pwd();
		if (!pwdtemp)
		{
			free(keytemp);
			free(pwdtemp);
			return ;
		}
		keyvalue = ft_strjoin(keytemp, pwdtemp);
		free(keytemp);
		free(pwdtemp);
		free(((t_kms *)curr->content)->key);
		free(((t_kms *)curr->content)->val);
		update_keymap((t_kms *)curr->content, keyvalue);
		free(keyvalue);
	}
}
