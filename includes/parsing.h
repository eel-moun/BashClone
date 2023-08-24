/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:08:58 by btaha             #+#    #+#             */
/*   Updated: 2023/01/09 20:10:22 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

typedef struct s_tree{
	t_list			*value;
	t_type			type;
	struct s_tree	*right;
	struct s_tree	*left;
}t_tree;

t_tree	*construct_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*dollar_quest_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*dollar_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*dlt_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*dgt_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*lt_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*gt_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*dq_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*sq_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*pipe_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*command_tree(t_lexer *lexer, t_tree *root_ast);
t_tree	*ft_init_tree(t_tree *ast);
t_tree	*pipeline(t_lexer *lexer);
int		check_command(t_list *command, t_type type, t_tree *tree);
int		manage_tree(t_tree *root_tree, int std_in[2], int std_out[2]);
char	*get_var_name(t_lexer *lexer);
#endif