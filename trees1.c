/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:18:44 by btaha             #+#    #+#             */
/*   Updated: 2023/01/13 20:33:20 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_tree	*command_tree(t_lexer *lexer, t_tree *ast)
{
	t_token	*token;
	t_tree	*temp;

	if (!ast)
		ast = ft_init_tree(ast);
	temp = ast;
	while (temp && temp->right)
	{
		if (temp->type != PIPE && !check_if_rdr(temp))
			break ;
		temp = temp->right;
	}
	token = lexer_next_token(lexer);
	if (token->type == COMMAND)
	{
		temp->type = COMMAND;
		ft_lstadd_back(&temp->value, ft_lstnew(token->value));
	}
	return (ast);
}

t_tree	*sq_tree(t_lexer *lexer, t_tree *ast)
{
	int		j;
	char	*str;
	t_tree	*temp;

	if (!ast)
		ast = ft_init_tree(ast);
	temp = ast;
	advance(&temp);
	j = 0;
	lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->c != '\0')
	{
		lexer_advance(lexer);
		j++;
	}
	if (lexer->c == '\0')
		return (ft_printf(2, "unfinished '\n"), NULL);
	str = malloc(j * sizeof(char) + 1);
	ft_strlcpy(str, &lexer->src[(lexer->i) - j], j + 1);
	lexer_advance(lexer);
	return (ft_lstadd_back(&temp->value, ft_lstnew(str)), ast);
}

t_tree	*dollar_tree(t_lexer *lexer, t_tree *ast)
{
	char	*str;
	char	*var_name;
	t_tree	*temp;

	if (!ast)
		ast = ft_init_tree(ast);
	temp = ast;
	while (temp && temp->right)
	{
		if (temp->type != PIPE && !check_if_rdr(temp))
			break ;
		temp = temp->right;
	}
	var_name = get_var_name(lexer);
	if (!ft_strcmp(var_name, "?"))
		str = ft_itoa(g_shell.exit);
	else
		str = ft_getenv(var_name);
	if (str != NULL)
		ft_lstadd_back(&temp->value, ft_lstnew(str));
	temp->type = DOLLAR;
	return (ast);
}

static void	norm(t_lexer **lexer, t_tree **temp, char **str, int *j)
{
	lexer_advance((*lexer));
	while ((*lexer)->c != '"' && (*lexer)->c != '\0' && (*lexer)->c != '$')
	{
		lexer_advance((*lexer));
		*j += 1;
	}
	while ((*lexer)->c == '$')
	{
		(*str) = malloc(*j * sizeof(char) + 1);
		ft_strlcpy((*str), &(*lexer)->src[((*lexer)->i) - *j], *j + 1);
		if ((*str) != NULL)
			ft_lstadd_back(&(*temp)->value, ft_lstnew((*str)));
		(*temp) = construct_tree((*lexer), (*temp));
		*j = 0;
		while ((*lexer)->c != '"' && (*lexer)->c != '\0' && (*lexer)->c != '$')
		{
			lexer_advance((*lexer));
			*j += 1;
		}
	}
	while ((*lexer)->c != '"' && (*lexer)->c != '\0' && (*lexer)->c != '$')
	{
		lexer_advance((*lexer));
		*j += 1;
	}
}

t_tree	*dq_tree(t_lexer *lexer, t_tree *ast)
{
	int		j;
	char	*str;
	t_tree	*temp;

	if (!ast)
		ast = ft_init_tree(ast);
	temp = ast;
	advance(&temp);
	j = 0;
	norm(&lexer, &temp, &str, &j);
	if (lexer->c == '\0')
		return (ft_printf(2, "unfinished \"\n"), NULL);
	str = malloc(j * sizeof(char) + 1);
	ft_strlcpy(str, &lexer->src[(lexer->i) - j], j + 1);
	if (lexer->c == '"')
		lexer_advance(lexer);
	ft_lstadd_back(&temp->value, ft_lstnew(str));
	return (ast);
}
