/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:19:37 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 21:31:05 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_tree	*pipe_tree(t_lexer *lexer, t_tree *ast)
{
	t_tree	*root_ast;

	if (!ast)
	{
		return (ft_printf(2, "minishell: parse error near '||'\n"),
			g_shell.error = 1, NULL);
	}
	root_ast = ft_init_tree(NULL);
	lexer_advance(lexer);
	root_ast->left = ast;
	root_ast->type = PIPE;
	root_ast->right = construct_tree(lexer, root_ast->right);
	return (root_ast);
}

t_tree	*gt_tree(t_lexer *lexer, t_tree *ast)
{
	t_tree	*root_ast;

	if (!ast)
		ast = ft_init_tree(NULL);
	root_ast = ft_init_tree(NULL);
	lexer_advance(lexer);
	root_ast->left = ast;
	root_ast->type = GREATER_THAN;
	root_ast->right = construct_tree(lexer, root_ast->right);
	return (root_ast);
}

t_tree	*dgt_tree(t_lexer *lexer, t_tree *ast)
{
	t_tree	*root_ast;

	if (!ast)
		ast = ft_init_tree(NULL);
	root_ast = ft_init_tree(NULL);
	lexer_advance(lexer);
	lexer_advance(lexer);
	root_ast->left = ast;
	root_ast->type = DGREATER_THAN;
	root_ast->right = construct_tree(lexer, root_ast->right);
	return (root_ast);
}

t_tree	*lt_tree(t_lexer *lexer, t_tree *ast)
{
	t_tree	*root_ast;

	if (!ast)
		ast = ft_init_tree(NULL);
	root_ast = ft_init_tree(NULL);
	lexer_advance(lexer);
	lexer_advance(lexer);
	root_ast->left = ast;
	root_ast->type = LOWER_THAN;
	root_ast->right = construct_tree(lexer, root_ast->right);
	return (root_ast);
}

t_tree	*dlt_tree(t_lexer *lexer, t_tree *ast)
{
	t_tree	*root_ast;

	if (!ast)
		ast = ft_init_tree(NULL);
	root_ast = ft_init_tree(NULL);
	lexer_advance(lexer);
	lexer_advance(lexer);
	root_ast->left = ast;
	root_ast->type = DLOWER_THAN;
	root_ast->right = construct_tree(lexer, root_ast->right);
	return (root_ast);
}
