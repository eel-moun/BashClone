/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:16:03 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 22:13:57 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_shell	g_shell;

static void	free_shell(t_list **env)
{
	t_list	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free_env((*env)->content);
		free(*env);
		*env = tmp;
	}
}

int	init_all(char *env[], int ac, char *av[])
{
	(void) ac;
	(void) av;
	g_shell.exit = 0;
	g_shell.env = NULL;
	g_shell.exec = 0;
	g_shell.error = 0;
	g_shell.args = NULL;
	if (init_env(env))
		return (perror("minishell"),
			ft_lstclear(&g_shell.env, (t_delfn)free_env), -1);
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	t_lexer	*lexer;
	t_tree	*tree;
	char	*line;

	if (init_all(envp, ac, av) || set_sig(1))
		return (1);
	line = readline("minishell-1.0$ ");
	while (line)
	{
		if (ft_strcheck(line, " \t\n") < ft_strlen(line))
			add_history(line);
		lexer = init_lexer(line);
		if (lexer)
		{
			g_shell.exec = 1;
			tree = pipeline(lexer);
			if (exec(tree, NULL, NULL, 1))
				g_shell.exit = 1;
			g_shell.exec = 0;
		}
		free(line);
		line = readline("minishell-1.0$ ");
	}
	return (ft_printf(1, "exit\n"), free_shell(&g_shell.env), g_shell.exit);
}
