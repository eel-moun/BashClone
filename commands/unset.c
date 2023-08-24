/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:47:35 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 16:42:21 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_e(char *arg)
{
	ft_printf(2, "minishell: unset: '%s': not a valid identifier\n", arg);
	return (0);
}

int	unset_env(char *name)
{
	t_list	*lst;

	if (!name || !*name || ft_strchr(name, '='))
		return (-1);
	lst = find_name(g_shell.env, name);
	if (lst)
	{
		ft_lstremove(&g_shell.env, lst);
		ft_lstdelone(lst, (void *)free_env);
	}
	return (0);
}

int	unset(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i++]))
		return (print_e(arg));
	while (ft_isalnum(arg[i]))
	{
		i++;
	}
	if (arg[i] != '\0')
		return (print_e(arg));
	if (unset_env(arg))
		return (ft_printf(2, "minishell: unset: '%s", arg), perror("': "), 0);
	return (1);
}

int	ft_unset(t_list *args)
{
	g_shell.exit = 0;
	while (args)
	{
		if (!unset(args->content))
			g_shell.exit = 1;
		args = args->next;
	}
	return (0);
}
