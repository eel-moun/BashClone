/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:05:29 by btaha             #+#    #+#             */
/*   Updated: 2023/01/13 20:15:58 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_option(char *arg, int n)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[++i] && n != 0)
	{
		while (arg[i] == 'n')
		{
			i++;
		}
		if (!arg[i])
			return (0);
	}
	return (1);
}

static int	ft_check(t_list *args)
{
	if (!ft_strcmp(args->content, "'"))
		return (0);
	else if (!ft_strcmp(args->content, "\""))
		return (0);
	if (!args->next)
		return (1);
	else if (!ft_strcmp(args->next->content, "\""))
		return (0);
	if (!ft_strcmp(args->next->content, "'"))
		return (0);
	else
		return (1);
}

int	ft_echo(t_list *args, t_type type)
{
	int		i;
	int		n;

	g_shell.exit = 0;
	if (!args || !args->content)
		return (ft_printf(1, "\n"), 0);
	i = 0;
	n = check_option(args->content, 1);
	if (n == 0)
		args = args->next;
	i = 0;
	(void)type;
	while (args)
	{
		if (i > 0 && ft_check(args))
			ft_printf(1, " ");
		ft_printf(1, "%s", args->content);
		args = args->next;
		i++;
	}
	if (n == 1)
		ft_printf(1, "\n");
	return (0);
}
