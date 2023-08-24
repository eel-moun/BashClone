/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:46:15 by btaha             #+#    #+#             */
/*   Updated: 2023/01/12 20:57:13 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_left(t_tree *tree, int n)
{
	while (check_if_rdr(tree) && tree)
	{
		n++;
		tree = tree->left;
	}
	return (n);
}

void	check_args(void)
{
	if (g_shell.args)
		g_shell.args = NULL;
}

int	check_rdr_i(t_tree *tmp, int n, t_tree **temp, int *j)
{
	char	*file;

	while (n > 1)
	{
		n--;
		tmp = tmp->left;
	}
	if (tmp->type == LOWER_THAN)
	{
		file = tmp->right->value->content;
		if (open_file(file, tmp->type) == -1)
			return (-1);
	}
	else if (tmp->type == DLOWER_THAN)
	{
		file = filename(tmp->right->value->content);
		if (open_file(file, tmp->type) == -1)
			return (-1);
	}
	if (tmp->right->value->next)
		ft_lstadd_back(&g_shell.args, tmp->right->value->next);
	*j -= 1;
	(*temp) = (*temp)->left;
	return (1);
}

int	check_rdr_o(t_tree *tmp, int n, t_tree **temp, int *j)
{
	char	*file;

	file = NULL;
	while (n > 1)
	{
		n--;
		tmp = tmp->left;
	}
	if (tmp->type == GREATER_THAN || tmp->type == DGREATER_THAN)
	{
		file = tmp->right->value->content;
		if (open_file(file, tmp->type) == -1)
			return (-1);
	}
	if (tmp->right->value->next)
		ft_lstadd_back(&g_shell.args, tmp->right->value->next);
	(*temp) = (*temp)->left;
	*j -= 1;
	return (1);
}

int	check_if_rdr(t_tree *tree)
{
	t_type	type;

	type = tree->type;
	if (type == GREATER_THAN || type == DGREATER_THAN
		|| type == LOWER_THAN || type == DLOWER_THAN)
		return (1);
	else
		return (0);
}
