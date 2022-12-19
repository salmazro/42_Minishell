/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:56:14 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ft_printf.h"

char	ft_getspecifier(const char *input, t_plist *alist)
{
	if (input[alist -> i] == '%')
		alist -> i++;
	if (pf_strchr("cspdiuxX%", input[alist->i], alist) != 0)
		return (input[alist->i]);
	return (0);
}

void	ft_speci(const char input, int fd, t_plist *alist)
{
	if (input == 'c')
		ft_putchar(va_arg(alist->arg, int), fd, alist);
	else if (input == 'd' || input == 'i')
		ft_putnbr_base(va_arg(alist->arg, int), "0123456789", fd, alist);
	else if (input == 's')
		ft_putstr(va_arg(alist->arg, char *), fd, alist);
	else if (input == 'u')
		ft_putnbr_base(va_arg(alist->arg, unsigned int),
			"0123456789", fd, alist);
	else if (input == 'x')
		ft_putnbr_base(va_arg(alist->arg, unsigned int),
			"0123456789abcdef", fd, alist);
	else if (input == 'X')
		ft_putnbr_base(va_arg(alist->arg, unsigned int),
			"0123456789ABCDEF", fd, alist);
	else if (input == 'p')
	{
		write(fd, "0x", 2);
		alist->ret += 2;
		ft_print_mem(va_arg(alist->arg, unsigned long long),
			"0123456789abcdef", fd, alist);
	}
}

int	ft_printf(const char *ip, ...)
{
	t_plist	st;
	int		i;

	i = 0;
	st.ret = 0;
	va_start(st.arg, ip);
	while (ip[i])
	{
		if (ip[i] == '%')
		{
			i++;
			if (ip[i] == '%')
				ft_putchar(ip[i], 1, &st);
			else
				ft_speci(ip[i], 1, &st);
			i++;
		}
		else
			pf_putchar_fd(ip[i++], 1, &st);
	}
	va_end(st.arg);
	return (st.ret);
}

int	ft_fprintf(int fd, const char *ip, ...)
{
	t_plist	st;
	int		i;

	i = 0;
	st.ret = 0;
	va_start(st.arg, ip);
	while (ip[i])
	{
		if (ip[i] == '%')
		{
			i++;
			if (ip[i] == '%')
				ft_putchar(ip[i], fd, &st);
			else
				ft_speci(ip[i], fd, &st);
			i++;
		}
		else
			pf_putchar_fd(ip[i++], fd, &st);
	}
	va_end(st.arg);
	return (st.ret);
}
