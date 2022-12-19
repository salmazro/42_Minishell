/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:51:19 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*x;
	t_list	*new;

	new = NULL;
	while (lst)
	{
		x = ft_lstnew(f(lst->content));
		if (!x)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&new, x);
		lst = lst->next;
	}
	return (new);
}
