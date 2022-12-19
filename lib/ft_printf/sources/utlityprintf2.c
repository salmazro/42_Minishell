/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlityprintf2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:56:24 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_helper(char *base, int fd, t_plist *alist, long n)
{
	int	base_len;

	base_len = pf_strlen(base);
	if (n < base_len)
	{
		write(fd, &base[n], 1);
		alist -> ret ++;
	}
}

int	ft_putnbr_base(long long nbr, char *base, int fd, t_plist *alist)
{
	long	n;
	int		base_len;

	n = 0;
	alist->negat = 0;
	if (n < 0)
		alist->negat = 1;
	n = nbr;
	base_len = pf_strlen(base);
	if (nbr < 0)
	{
		write(fd, "-", 1);
		n = -n;
		alist->ret++;
	}
	ft_putnbr_base_helper(base, fd, alist, n);
	if (n >= base_len)
	{
		ft_putnbr_base(n / base_len, base, fd, alist);
		write (fd, &base[n % base_len], 1);
		alist -> ret++;
	}
	return (num_size(n, base_len, alist) + alist->negat);
}

int	ft_print_mem(unsigned long long nbr, char *base, int fd, t_plist *alist)
{
	unsigned long long	n;

	n = nbr;
	alist -> i = 0;
	if (nbr == 0)
	{
		write (fd, "0", 1);
		alist -> ret ++;
		return (1);
	}
	if (n < 16)
	{
		alist -> i++;
		write (fd, &base[n], 1);
		alist -> ret ++;
	}
	if (n >= 16)
	{
		alist -> i += ft_putnbr_base(n / 16, base, fd, alist);
		write (fd, &base[n % 16], 1);
		alist -> ret ++;
	}
	return (num_size(nbr, 16, alist));
}

void	ft_putstr(char *s, int fd, t_plist *alist)
{
	int	j;

	if (s == NULL)
	{
		write (fd, "(null)", 6);
		alist->ret += 6;
		alist->i++;
	}
	else
	{
		j = pf_strlen(s);
		write (fd, s, j);
		alist->ret += j;
		alist->i++;
	}
}

int	nbrlen(unsigned int num, t_plist *alist)
{
	alist->i = 0;
	while (num > 0)
	{
		num /= 10;
		alist -> i++;
	}
	return (alist -> i);
}
