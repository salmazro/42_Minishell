/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:59:00 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_keymap(void *content)
{
	t_kms	*km;

	km = (t_kms *)content;
	free(km->key);
	if (km->val && *km->val)
		free(km->val);
	free(km);
}

void	clear_env(t_env *env)
{
	if (!env)
		return ;
	ft_clearsplit(env->env);
	ft_lstclear(&env->kms, clear_keymap);
	free(env->kms);
	free(env);
}
