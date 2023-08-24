/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:20:41 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:00:31 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_list *args)
{
	t_list	*tmp;
	t_env	*line;

	g_shell.exit = 0;
	while (args)
	{
		if (!ft_strcmp(args->content, "env"))
		{
			args = args->next;
			continue ;
		}
		return (ft_printf(2, "env: %s: No such file or directory\n",
				args->content),
			g_shell.exit = 1, 0);
		args = args->next;
	}
	tmp = g_shell.env;
	while (tmp)
	{
		line = tmp->content;
		if (line->print == 1)
			ft_printf(1, "%s=%s\n", line->name, line->value);
		tmp = tmp->next;
	}
	return (0);
}
