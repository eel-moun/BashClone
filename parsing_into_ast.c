/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_into_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:16:32 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 21:31:23 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_tree	*pipeline(t_lexer *lexer)
{
	t_tree	*ast;

	ast = ft_init_tree(NULL);
	while (lexer->c != '\0')
	{
		ast = construct_tree(lexer, ast);
		if (g_shell.error == 1)
			return (g_shell.error = 0, NULL);
	}
	return (ast);
}

t_tree	*construct_tree(t_lexer *lexer, t_tree *root_ast)
{
	t_token	*token;

	token = lexer_alt_next_token(lexer);
	lexer_skip_whitespace(lexer);
	if (token->type == SINGLE_QUOTE)
		return (sq_tree(lexer, root_ast));
	else if (token->type == DOUBLE_QUOTE)
		return (dq_tree(lexer, root_ast));
	else if (token->type == DOLLAR)
		return (dollar_tree(lexer, root_ast));
	else if (token->type == PIPE)
		return (pipe_tree(lexer, root_ast));
	else if (token->type == GREATER_THAN)
		return (gt_tree(lexer, root_ast));
	else if (token->type == DGREATER_THAN)
		return (dgt_tree(lexer, root_ast));
	else if (token->type == LOWER_THAN)
		return (lt_tree(lexer, root_ast));
	else if (token->type == DLOWER_THAN)
		return (dlt_tree(lexer, root_ast));
	else
		return (command_tree(lexer, root_ast));
}
