/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:15:11 by btaha             #+#    #+#             */
/*   Updated: 2023/01/08 14:10:16 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_list	*find_name(t_list *env, char *name)
{
	t_env	*lst;

	while (env)
	{
		lst = env->content;
		if (!ft_strcmp(lst->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	update_env(t_env *env, char *value, int print)
{
	char	*v;

	if (!env->value && !value)
		return (0);
	v = NULL;
	if (value)
	{
		v = ft_strdup(value);
		if (!v)
			return (-1);
	}
	return (free(env->value), env->value = v, env->print = print, 0);
}

int	add_env(char *name, char *value, int print)
{
	t_list	*lst;
	t_env	*env;

	env = set_var(name, value);
	env->print = print;
	lst = ft_lstnew(env);
	if (!lst || !env)
		return (free_env(env), ft_lstdelone(lst, NULL), -1);
	return (ft_lstadd_front(&g_shell.env, lst), 0);
}

int	set_env(char *name, char *value, int print)
{
	t_list	*lst;

	if (!name || !*name || ft_strchr(name, '='))
		return (-1);
	lst = find_name(g_shell.env, name);
	if (!lst)
		return (add_env(name, value, print));
	return (update_env(lst->content, value, print));
}
