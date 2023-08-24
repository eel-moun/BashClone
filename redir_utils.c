/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:29:15 by btaha             #+#    #+#             */
/*   Updated: 2023/01/12 21:09:41 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	open_file(char *file, t_type type)
{
	int		fd;

	fd = -1;
	if (type == LOWER_THAN || type == DLOWER_THAN)
		fd = open(file, O_RDONLY);
	else if (type == DGREATER_THAN)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0664);
	else if (type == GREATER_THAN)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd == -1)
		return (ft_printf(2, "minishell: %s: ", file), perror(NULL), -1);
	return (fd);
}

static	int	stdio_dup(int stdio[2])
{
	if (!stdio)
		return (0);
	stdio[0] = dup(0);
	if (stdio[0] == -1)
		return (perror("minishell"), -1);
	stdio[1] = dup(1);
	if (stdio[1] == -1)
		return (perror("minishell"), -1);
	return (0);
}

int	stdio_dup2(t_type type, int fd)
{
	int	fd_dup2;

	fd_dup2 = -1;
	if (type == LOWER_THAN || type == DLOWER_THAN)
		fd_dup2 = dup2(fd, STDIN_FILENO);
	else
		fd_dup2 = dup2(fd, STDOUT_FILENO);
	if (fd_dup2 == -1)
		perror("minishell");
	return (fd_dup2);
}

int	exec_rdr(t_tree *tree, int stdio[2], t_type type, char *file)
{
	int		fd[2];

	if (stdio_dup(stdio))
		return (-1);
	if (!file && type != DLOWER_THAN)
		file = tree->value->content;
	else
		file = filename(tree->value->content);
	fd[0] = open_file(file, type);
	if (fd[0] == -1)
		return (close(fd[0]), stdio_res(stdio), -1);
	fd[1] = stdio_dup2(type, fd[0]);
	if (fd[0] == -1 || fd[1] == -1)
		return (close(fd[0]), stdio_res(stdio), -1);
	close(fd[0]);
	return (0);
}

int	check_rdr(t_tree *tree, int stdio[2], char *file)
{
	t_type	type;

	type = tree->type;
	if (check_if_rdr(tree))
	{
		if (!tree->right)
			return (exec_rdr(tree, stdio, type, file));
		else
			return (exec_rdr(tree->right, stdio, type, file));
	}
	return (0);
}
