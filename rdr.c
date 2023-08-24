/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:25:03 by btaha             #+#    #+#             */
/*   Updated: 2023/01/12 21:31:05 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_expand(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i++] == '$')
			return (1);
	}
	return (0);
}

char	*expand(t_lexer *lexer)
{
	char	*str;
	char	*var_name;

	var_name = get_var_name(lexer);
	if (!ft_strcmp(var_name, "?"))
		str = ft_itoa(g_shell.exit);
	else
		str = ft_getenv(var_name);
	return (str);
}

static	int	write_heredoc_line(char *file, int fd, char *line)
{
	t_lexer	*exp;
	char	*nadi;

	exp = init_lexer(line);
	nadi = "";
	if (!line)
		return (close(fd), unlink(file), free(file), free(line), -1);
	while (exp->c)
	{
		if (exp->c == '$')
			nadi = ft_strjoin(nadi, expand(exp));
		else
			nadi = ft_strjoin(nadi, &exp->c);
		lexer_advance(exp);
	}
	if (ft_strlen(nadi) > 0)
		return (ft_putstr_fd(nadi, fd), ft_putchar_fd('\n', fd), free(nadi), 0);
	return (ft_putstr_fd(nadi, fd), ft_putchar_fd('\n', fd), 0);
}

static	int	read_heredoc(char *file, char *delime)
{
	char	*line;
	int		fd;

	rl_event_hook = event;
	signal(SIGINT, handler);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(file, 2),
			ft_putstr_fd(": ", 2), perror(NULL), fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (g_shell.exec == -1)
			return (0);
		if (!strcmp(line, delime))
			break ;
		if (write_heredoc_line(file, fd, line))
			return (-1);
		free(line);
	}
	return (free(line), close(fd), 0);
}

char	*filename(char *str)
{
	static int	n = 0;
	char		*n_str;
	char		*delim;
	char		*file;

	n_str = ft_itoa(n);
	delim = ft_substr(str, 0, ft_strlen(str));
	if (n_str)
		file = ft_strjoin("/tmp/minishell-heredoc-", n_str);
	free(n_str);
	if (!delim || !n_str || !file || read_heredoc(file, delim))
		return (perror("minishell"), free(delim), free(file), NULL);
	return (free(delim), n++, file);
}
