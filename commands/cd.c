/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:48:22 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 16:49:35 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_list *directorie)
{
	char	*user;

	g_shell.exit = 0;
	user = ft_getenv("USER");
	if (!directorie)
		chdir(ft_strjoin("/Users/", user));
	else if (chdir(directorie->content) < 0)
	{
		g_shell.exit = 1;
		return (perror("cd"), 0);
	}
	return (0);
}
