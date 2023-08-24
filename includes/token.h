/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:10:32 by btaha             #+#    #+#             */
/*   Updated: 2023/01/02 17:11:24 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "minishell.h"

typedef enum e_type{
	COMMAND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	GREATER_THAN,
	LOWER_THAN,
	DGREATER_THAN,
	DLOWER_THAN,
	PIPE,
	DOLLAR,
	DOLLAR_QUEST,
	WALOU,
}t_type;
typedef struct s_token
{
	char	*value;
	t_type	type;
}t_token;
t_token	*init_token(char *value, int type);

#endif