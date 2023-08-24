/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 09:41:35 by eel-moun          #+#    #+#             */
/*   Updated: 2022/12/27 14:13:11 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_alpha(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i++]))
		return (0);
	else
	{
		while (str[i])
		{
			if (!ft_isalnum(str[i++]))
				return (0);
		}
	}
	return (1);
}

int	ft_isalpha(int alpha)
{
	if ((alpha >= 97 && alpha <= 122) || (alpha >= 65 && alpha <= 90)
		|| alpha == '_')
		return (1);
	return (0);
}
