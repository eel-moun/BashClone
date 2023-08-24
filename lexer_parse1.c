/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:15:42 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:45:06 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_iscmd(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\n' || c == '\f')
		return (0);
	else if (c == '|' || c == '<' || c == '>'
		|| c == '$' || c == '"' || c == '\'')
		return (0);
	else
		return (1);
}

t_token	*lexer_parse_command(t_lexer *lexer)
{
	int		j;
	char	*str;

	j = 0;
	while (ft_iscmd(lexer->c) && lexer->c != '\0')
	{
		lexer_advance(lexer);
		j++;
	}
	str = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(str, &lexer->src[(lexer->i) - j], j + 1);
	return (init_token(str, COMMAND));
}

t_token	*lexer_parse_sc(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	*str = '\'';
	lexer_advance(lexer);
	return (init_token(str, SINGLE_QUOTE));
}

t_token	*lexer_parse_dc(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	*str = '"';
	lexer_advance(lexer);
	return (init_token(str, DOUBLE_QUOTE));
}

t_token	*lexer_parse_dollar(t_lexer *lexer)
{
	char	*str;

	if (lexer_peek(lexer) == ' ' || lexer_peek(lexer) == '\0')
	{
		str = ft_calloc(2, sizeof(char));
		*str = '$';
		lexer_advance(lexer);
		return (init_token(str, COMMAND));
	}
	else
	{
		str = ft_calloc(2, sizeof(char));
		*str = '$';
		lexer_advance(lexer);
		return (init_token(str, DOLLAR));
	}
}
