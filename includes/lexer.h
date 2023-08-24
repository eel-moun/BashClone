/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:05:40 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:07:01 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

typedef struct s_lexer{
	char			*src;
	size_t			src_size;
	char			c;
	unsigned int	i;
}t_lexer;

int		ft_iscmd(char c);
t_lexer	*init_lexer(char *src);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
char	lexer_peek(t_lexer *lexer);
t_token	*lexer_next_token(t_lexer *lexer);
t_token	*lexer_parse_command(t_lexer *lexer);
t_token	*lexer_parse_str(t_lexer *lexer);
t_token	*lexer_parse_sc(t_lexer *lexer);
t_token	*lexer_parse_dc(t_lexer *lexer);
t_token	*lexer_parse_pipe(t_lexer *lexer);
t_token	*lexer_parse_gt(t_lexer *lexer);
t_token	*lexer_parse_lt(t_lexer *lexer);
t_token	*lexer_parse_dollar(t_lexer *lexer);
t_token	*lexer_alt_next_token(t_lexer *lexer);
#endif