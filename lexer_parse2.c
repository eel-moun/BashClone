/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:15:49 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:15:50 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_token	*lexer_parse_pipe(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	*str = '|';
	lexer_advance(lexer);
	return (init_token(str, PIPE));
}

t_token	*lexer_parse_gt(t_lexer *lexer)
{
	char	*str;

	if (lexer_peek(lexer) == '>')
	{
		str = ft_calloc(3, sizeof(char));
		ft_strlcpy(str, &lexer->src[lexer->i], 3);
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_token(str, DGREATER_THAN));
	}
	else
	{
		str = ft_calloc(2, sizeof(char));
		*str = '>';
		lexer_advance(lexer);
		return (init_token(str, GREATER_THAN));
	}
}

t_token	*lexer_parse_lt(t_lexer *lexer)
{
	char	*str;

	if (lexer_peek(lexer) == '<')
	{
		str = ft_calloc(3, sizeof(char));
		ft_strlcpy(str, &lexer->src[lexer->i], 3);
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_token(str, DLOWER_THAN));
	}
	else
	{
		str = ft_calloc(2, sizeof(char));
		*str = '<';
		lexer_advance(lexer);
		return (init_token(str, LOWER_THAN));
	}
}
