/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:17:11 by btaha             #+#    #+#             */
/*   Updated: 2023/01/13 20:30:43 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == '\'')
			return (lexer_parse_sc(lexer));
		else if (lexer->c == '"')
			return (lexer_parse_dc(lexer));
		else if (lexer->c == '>')
			return (lexer_parse_gt(lexer));
		else if (lexer->c == '<')
			return (lexer_parse_lt(lexer));
		else if (lexer->c == '|')
			return (lexer_parse_pipe(lexer));
		else if (lexer->c == '$')
			return (lexer_parse_dollar(lexer));
		else if (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\r'
			|| lexer->c == '\v' || lexer->c == '\n' || lexer->c == '\f')
			lexer_skip_whitespace(lexer);
		else
			return (lexer_parse_command(lexer));
	}
	return (init_token("\0", WALOU));
}

t_token	*lexer_alt_next_token(t_lexer *lexer)
{
	int		i;
	t_token	*token;

	i = lexer->i;
	token = lexer_next_token(lexer);
	lexer->i = i;
	lexer->c = lexer->src[lexer->i];
	return (token);
}

void	advance(t_tree **temp)
{
	while ((*temp) && (*temp)->right)
	{
		if ((*temp)->type != PIPE && !check_if_rdr((*temp)))
			break ;
		(*temp) = (*temp)->right;
	}
}
