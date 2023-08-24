/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:53:04 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 22:42:52 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <assert.h>
# include <stdarg.h>

char	ft_strchr_d(const char *s, int c);
int		ft_putstr_d(char *s, int fd);
int		ft_putchar_d(char c, int fd);
void	ft_putnbr_d(int n, int *count, int fd);
int		ft_printf(int fd, const char *c, ...);
int		ft_to_hex(size_t num, int *count, char cap, int fd);
void	ft_putnbru(unsigned int n, int *count, int fd);
int		ft_pointer(size_t p, int fd);

#endif
