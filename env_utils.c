/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:13:32 by btaha             #+#    #+#             */
/*   Updated: 2023/01/03 17:38:47 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	free_env(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}

char	*ft_getenv(char *name)
{
	t_list	*lst;
	t_env	*env;

	if (!name || !*name || ft_strchr(name, '='))
		return (NULL);
	lst = g_shell.env;
	while (lst)
	{
		env = lst->content;
		if (!ft_strcmp(env->name, name))
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}

t_env	*set_var(char *name, char *value)
{
	t_env	*env;
	char	*n;
	char	*v;

	env = malloc(sizeof(t_env));
	n = ft_strdup(name);
	v = NULL;
	if (value)
		v = ft_strdup(value);
	if (!env || !name || (value && !v))
		return (free(env), free(n), free(v), NULL);
	env->print = 1;
	return (env->name = n, env->value = v, env);
}

int	init_env(char *envp[])
{
	int		i;
	t_env	*line;
	t_list	*lst;
	char	**tab;

	i = 0;
	while (envp[i])
	{
		tab = ft_split(envp[i], '=');
		line = set_var(tab[0], tab[1]);
		lst = ft_lstnew(line);
		if (!line || !lst)
			return (free_env(line), free(lst), -1);
		ft_lstadd_back(&g_shell.env, lst);
		i++;
	}
	return (free(tab), 0);
}
