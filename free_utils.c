/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:43:42 by btaha             #+#    #+#             */
/*   Updated: 2023/01/13 21:09:06 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	free_tree_node(t_tree *tree)
{
	if (!tree)
		return ;
	ft_lstclear(&tree->value, free);
	free(tree);
}

void	free_tree(t_tree **parse)
{
	t_tree	*tree;

	tree = *parse;
	if (!tree)
		return ;
	if (tree->type == DLOWER_THAN && tree->right->value)
		unlink(tree->right->value->content);
	free_tree(&tree->left);
	free_tree(&tree->right);
	free_tree_node(tree);
	*parse = NULL;
}
