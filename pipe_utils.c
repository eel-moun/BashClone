/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:06:13 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 22:14:41 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_pipe(t_tree *tree)
{
	while (tree)
	{
		if (tree->type == PIPE)
			return (1);
		tree = tree->left;
	}
	return (0);
}

int	check_if_command(t_list *command)
{
	if (!command || !command->content)
		return (0);
	else if (!ft_strcmp(command->content, "echo"))
		return (1);
	else if (!ft_strcmp(command->content, "cd"))
		return (1);
	else if (!ft_strcmp(command->content, "env"))
		return (1);
	else if (!ft_strcmp(command->content, "export"))
		return (1);
	else if (!ft_strcmp(command->content, "pwd"))
		return (1);
	else if (!ft_strcmp(command->content, "unset"))
		return (1);
	else if (!ft_strcmp(command->content, "exit"))
		return (1);
	else
		return (0);
}

int	exe_cmd_pid(t_tree *tree, int std_in[2], int std_out[2], t_type type)
{
	int	pid;

	pid = set_fork(std_in, std_out);
	if (pid)
		return (pid);
	if (!tree || !tree->value)
		exit(0);
	if (check_if_command(tree->value))
		return (check_command(tree->value, type, tree),
			exit(g_shell.exit), 0);
	exec_ve(tree->value);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->value->content, 2);
	if (ft_putstr_fd(": ", 2), errno == ENOENT
		&& !ft_strchr(tree->value->content, '/'))
		ft_putstr_fd("command not found\n", 2);
	else
		perror(NULL);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}

int	manage_pipe(t_tree *tree, int std_in[2], int std_out[2], int r)
{
	int		fd[2];
	int		pidl;
	int		pidr;
	t_type	type;
	t_tree	*tmp;

	type = tree->left->type;
	tmp = tree;
	r = 0;
	if (pipe(fd))
		return (perror("minishell"), -1);
	pidl = exec(tree->left, std_in, fd, 1);
	if (pidl == -1)
		return (close_pipe(fd), -1);
	pidr = exe_cmd_pid(tree->right, fd, std_out, type);
	if (pidr == -1)
		close_pipe(fd);
	close_pipe(fd);
	waitpid(pidr, NULL, 0);
	return (pidl);
}
