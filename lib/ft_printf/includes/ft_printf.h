/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:56:06 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include  <stdarg.h>
# include  <unistd.h>
# include  <limits.h>
# include  <stdio.h>
# include  <stdlib.h>

typedef struct s_plist
{
	size_t	i;
	va_list	arg;
	int		negat;
	int		len;
	int		leng;
	int		tmp;
	size_t	ret;
}	t_plist;

void	ft_putchar(char c, int fd, t_plist *alist);
int		num_size(int n, int base_len, t_plist *alist);
char	*pf_strchr(const char *s, int c, t_plist *alist);
void	pf_putchar_fd(char c, int fd, t_plist *alist);
int		nbrlen(unsigned int num, t_plist *alist);
size_t	pf_strlen(const char *str);
void	ft_putnbr_base_helper(char *base, int fd, t_plist *alist, long n);
int		ft_putnbr_base(long long nbr, char *base, int fd, t_plist *alist);
int		ft_print_mem(unsigned long long nbr, char *base,
			int fd, t_plist *alist);
void	ft_putstr(char *s, int fd, t_plist *alist);
int		ft_printf(const char *alhai, ...);
void	ft_speci(const char input, int fd, t_plist *alist);
char	ft_getspecifier(const char *input, t_plist *alist);
int		ft_fprintf(int fd, const char *ip, ...);

#endif
