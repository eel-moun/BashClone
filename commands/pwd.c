/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:02:51 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:03:09 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	s[MAXPATHLEN];

	g_shell.exit = 0;
	if (getcwd(s, MAXPATHLEN))
		ft_printf(1, "%s\n", s);
	else
		return (perror("minishell: pwd"), g_shell.exit = 1, 0);
	return (0);
}
