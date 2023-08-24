/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:39:09 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 22:41:16 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_d(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_d(char *s, int fd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (write(fd, "(null)", 6));
	while (s[i] != '\0')
		count += write(fd, &s[i++], 1);
	return (count);
}

static int	check(char ch, va_list pi, int fd)
{
	int	i;

	i = 0;
	if (ch == 'c')
		i = ft_putchar_d((char) va_arg(pi, int), fd);
	else if (ch == 's' )
		i = ft_putstr_d((char *) va_arg(pi, const char *), fd);
	else if (ch == 'i' || ch == 'd')
		ft_putnbr_d(va_arg(pi, int), &i, fd);
	else if (ch == 'x' || ch == 'X')
		ft_to_hex(va_arg(pi, unsigned int), &i, ch, fd);
	else if (ch == 'u')
		ft_putnbru(va_arg(pi, unsigned int), &i, fd);
	else if (ch == 'p')
		i = ft_pointer(va_arg(pi, size_t), fd);
	else if (ch == '%')
		i = ft_putchar_d(ch, fd);
	va_end(pi);
	return (i);
}

static int	print(char *str, va_list pi, int fd)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			ft_putchar_d(str[i++], fd);
		else
		{
			c = ft_strchr_d("cspdiuxX%", str[++i]);
			len = len + check(c, pi, fd) - 2;
			i++;
		}
	}
	return (len + i);
}

int	ft_printf(int fd, const char *c, ...)
{
	int		len;
	va_list	pi;

	va_start(pi, c);
	len = print((char *)c, pi, fd);
	return (len);
}
