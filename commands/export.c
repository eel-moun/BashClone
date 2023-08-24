/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:58:28 by btaha             #+#    #+#             */
/*   Updated: 2023/01/08 14:28:44 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_e(char *arg)
{
	ft_printf(2, "minishell: export: `%s': not a valid identifier\n", arg);
	return (0);
}

void	print_export(void)
{
	t_list	*tmp;
	t_env	*line;

	tmp = g_shell.env;
	while (tmp)
	{
		line = tmp->content;
		if (!ft_strcmp(line->name, "_"))
			break ;
		ft_printf(1, "declare -x %s", line->name);
		if (line->name && line->print == 0)
			ft_printf(1, "\n");
		else if (line->value)
			ft_printf(1, "=\"%s\"\n", line->value);
		else
			ft_printf(1, "=\"\"\n");
		tmp = tmp->next;
	}
}

char	*checking(char **str, int i)
{
	if (str[0][i] == '+' && str[0][i + 1] == '\0')
	{
		str[0][i] = '\0';
		if (ft_getenv(str[0]) && str[1])
			return (ft_strjoin(ft_getenv(str[0]), str[1]));
	}
	return (str[1]);
}

int	check_var(char *var)
{
	int		i;
	int		print;
	char	**nadi;

	i = 0;
	print = 1;
	nadi = ft_split(var, '=');
	if (!ft_isalpha(nadi[0][i++]))
		return (print_e(var), free(nadi), 1);
	while (ft_isalnum(nadi[0][i]))
		i++;
	if (ft_strchr(var, '='))
	{
		nadi[1] = checking(nadi, i);
	}
	else
		print = 0;
	if (nadi[0][i] != '\0')
		return (print_e(var), free(nadi), 1);
	if (set_env(nadi[0], nadi[1], print))
		return (ft_printf(2, "minishell: export: `%s", var),
			perror("': "), free(nadi), 1);
	return (free(nadi), 0);
}

int	ft_export(t_list *var)
{
	g_shell.exit = 0;
	if (!var)
		return (print_export(), 0);
	while (var)
	{
		if (check_var(var->content))
			g_shell.exit = 1;
		var = var->next;
	}
	return (0);
}
