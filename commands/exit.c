/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:09:52 by btaha             #+#    #+#             */
/*   Updated: 2023/01/10 13:01:53 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_list *args)
{
	int	i;

	i = 0;
	ft_printf(1, "exit\n");
	if (!args)
		exit(g_shell.exit);
	g_shell.exit = 0;
	while (args && i <= 2)
	{
		if (!ft_atoi(args->content))
			return (ft_printf(2,
					"minishell: exit: %s: numeric argument required\n",
					args->content), exit(255), 255);
		args = args->next;
		i++;
	}
	if (i >= 2)
	{
		g_shell.exit = 1;
		return (ft_printf(2,
				"minishell: exit: too many arguments\n"), g_shell.exit = 1, 0);
	}
	return (exit(0), 0);
}
