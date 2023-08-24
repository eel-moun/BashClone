/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:25:45 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 22:41:56 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_d(int n, int *count, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		num = -num;
		*count += ft_putchar_d('-', fd);
	}
	if (num < 10)
	{
		*count += ft_putchar_d(num + 48, fd);
	}
	else
	{
		ft_putnbr_d(num / 10, count, fd);
		ft_putnbr_d(num % 10, count, fd);
	}
}

int	ft_to_hex(size_t num, int *count, char cap, int fd)
{
	char	*hex;

	if (cap == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if ((num / 16) != 0)
		ft_to_hex(num / 16, count, cap, fd);
	*count += ft_putchar_d(hex[num % 16], fd);
	return (*count);
}

void	ft_putnbru(unsigned int n, int *count, int fd)
{
	unsigned long	num;

	num = n;
	if (num < 10)
	{
		*count += ft_putchar_d(num + 48, fd);
	}
	else
	{
		ft_putnbru(num / 10, count, fd);
		ft_putnbru(num % 10, count, fd);
	}
}

int	ft_pointer(size_t p, int fd)
{
	int	count;

	count = write(fd, "0x", 2);
	ft_to_hex(p, &count, 'x', fd);
	return (count);
}

char	ft_strchr_d(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char) c);
		i++;
	}
	if (s[i] == (char) c)
		return ((char) c);
	return (0);
}
