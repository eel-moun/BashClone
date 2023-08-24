/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:16:37 by btaha             #+#    #+#             */
/*   Updated: 2023/01/05 14:21:57 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./includes/minishell.h"

t_tree	*ft_init_tree(t_tree *ast)
{
	ast = ft_calloc(1, sizeof(t_tree));
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

char	*get_var_name(t_lexer *lexer)
{
	int		j;
	char	*env_var_name;

	j = 0;
	lexer_advance(lexer);
	if (lexer->c == '?')
	{
		env_var_name = ft_calloc(2, sizeof(char));
		*env_var_name = '?';
		lexer_advance(lexer);
		return (env_var_name);
	}
	while (ft_isalnum(lexer->c) && lexer->c != '\0')
	{
		lexer_advance(lexer);
		j++;
	}
	env_var_name = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(env_var_name, &lexer->src[(lexer->i) - j], j + 1);
	return (env_var_name);
}
