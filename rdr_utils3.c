/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:53:09 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 21:32:17 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	checking_rdr(t_tree	*tree, t_tree **tmp)
{
	int	j;

	j = check_left(tree, 0);
	if ((*tmp)->type == DGREATER_THAN || (*tmp)->type == GREATER_THAN)
	{
		while (j > 1)
			if (check_rdr_o(tree, j, tmp, &j) == -1)
				return (-1);
	}
	else if ((*tmp)->type == LOWER_THAN || (*tmp)->type == DLOWER_THAN)
		while (j > 1)
			if (check_rdr_i(tree, j, tmp, &j) == -1)
				return (-1);
	if (tree->type == DGREATER_THAN || tree->type == GREATER_THAN)
	{
		if (check_rdr_oi(tree) == -1 || check_rdr(tree, g_shell.fd, NULL) == -1)
			return (-1);
	}
	else
	{
		if (check_rdr_io(tree) == -1 || check_rdr(tree, g_shell.fd, NULL) == -1)
			return (-1);
	}
	return (0);
}

int	check_if_l(t_tree **tree)
{
	while ((*tree))
	{
		if ((*tree)->type == LOWER_THAN || (*tree)->type == DLOWER_THAN)
			return (1);
		(*tree) = (*tree)->left;
	}
	return (0);
}

int	check_if_g(t_tree **tree)
{
	while ((*tree))
	{
		if ((*tree)->type == GREATER_THAN || (*tree)->type == DGREATER_THAN)
			return (1);
		(*tree) = (*tree)->left;
	}
	return (0);
}

int	check_rdr_oi(t_tree *tree)
{
	t_tree	*tmp;
	int		j;

	if (check_if_l(&tree))
	{
		tmp = tree;
		j = check_left(tree, 0);
		while (j > 1)
			if (check_rdr_i(tree, j, &tmp, &j) == -1)
				return (-1);
		if (check_rdr(tree, g_shell.fd, NULL) == -1)
			return (-1);
	}
	return (1);
}

int	check_rdr_io(t_tree *tree)
{
	t_tree	*tmp;
	int		j;

	if (check_if_g(&tree))
	{
		tmp = tree;
		j = check_left(tree, 0);
		while (j > 1)
			if (check_rdr_o(tree, j, &tmp, &j) == -1)
				return (-1);
		if (check_rdr(tree, g_shell.fd, NULL) == -1)
			return (-1);
	}
	return (1);
}
