/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:13:56 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:13:58 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*get_path(char *cmd)
{
	char	*path;

	path = ft_strjoin("/bin/", cmd);
	if (!path)
		return (free(path), NULL);
	return (path);
}

size_t	get_len(t_list	*args)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

char	**get_args(t_list *cmd)
{
	char	**args;
	int		i;

	args = ft_calloc(get_len(cmd), sizeof(char **));
	if (!args)
		return (free(args), NULL);
	i = 0;
	while (cmd)
	{
		args[i++] = cmd->content;
		cmd = cmd->next;
	}
	return (args);
}

int	exe_exec(char *path, t_list *cmd)
{
	char	**args;
	char	**env;

	env = get_env();
	if (!env)
		return (-1);
	args = get_args(cmd);
	execve(path, args, env);
	free_str(env);
	return (-1);
}

int	exec_path(char *path_env, char *path, t_list *cmd)
{
	char	**tab;
	int		i;
	int		acces;

	tab = ft_split(path_env, ':');
	i = 0;
	acces = 1;
	while (tab[i])
	{
		exe_exec(ft_strjoin(tab[i++], path), cmd);
		if (errno == EACCES)
			acces = 0;
		else if (errno == ENOENT || errno == ENOTDIR)
			continue ;
		break ;
	}
	if (!acces)
		errno = EACCES;
	return (free(tab), -1);
}
