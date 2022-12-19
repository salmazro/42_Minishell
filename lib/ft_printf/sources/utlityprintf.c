/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlityprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:56:18 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int fd, t_plist *alist)
{
	write(fd, &c, 1);
	alist -> ret += 1;
	alist -> i += 1;
}

void	pf_putchar_fd(char c, int fd, t_plist *alist)
{
	write(fd, &c, 1);
	alist -> ret += 1;
}

int	num_size(int n, int base_len, t_plist *alist)
{
	alist->i = 1;
	while (n >= base_len)
	{
		n /= base_len;
		alist -> i++;
	}
	return (alist -> i);
}

char	*pf_strchr(const char *s, int c, t_plist *alist)
{
	char	j;

	j = (char) c;
	alist -> i = 0;
	if (c == 0)
		return ((char *)s + pf_strlen((char *)s));
	while (s[alist -> i])
	{
		if (s[alist->i] == j)
			return ((char *)s + alist -> i);
		alist->i++;
	}
	return (0);
}

size_t	pf_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}
