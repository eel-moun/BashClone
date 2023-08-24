/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:13:46 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:13:48 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	free_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static int	len_env(t_list *lst)
{
	t_env	*env;
	int		i;

	i = 1;
	while (lst)
	{
		env = lst->content;
		if (env->value)
			i++;
		lst = lst->next;
	}
	return (i);
}

static char	*allocat_env(t_env *env)
{
	char	*str;
	char	*s;

	s = ft_strjoin(env->name, "=");
	if (!s)
		return (NULL);
	str = ft_strjoin(s, env->value);
	if (!str)
		return (free(s), NULL);
	return (str);
}

char	**get_env(void)
{
	char	**env_p;
	t_list	*lst;
	t_env	*env;
	int		i;

	i = 0;
	lst = g_shell.env;
	env_p = malloc(sizeof(char *) * len_env(lst));
	if (!env_p)
		return (NULL);
	while (lst)
	{
		env = lst->content;
		if (env->value)
		{
			env_p[i] = allocat_env(env);
			if (!env_p[i])
				break ;
			i++;
		}
		lst = lst->next;
	}
	if (!env_p)
		return (free_str(env_p), NULL);
	return (env_p[i] = NULL, env_p);
}
