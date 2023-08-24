/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:14:03 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 21:36:20 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	exec_ve(t_list *cmd)
{
	char	*path_env;
	char	*path;

	errno = ENOENT;
	if (!cmd->content || !cmd)
		return (-1);
	if (ft_strchr(cmd->content, '/'))
		return (exe_exec(cmd->content, cmd));
	path_env = ft_getenv("PATH");
	path = ft_strjoin("/", cmd->content);
	if (!path_env)
		return (-1);
	return (exec_path(path_env, path, cmd));
}

int	check_command(t_list *command, t_type type, t_tree *tree)
{
	(void) tree;
	if (!ft_strcmp(command->content, "echo"))
		ft_echo(command->next, type);
	else if (!ft_strcmp(command->content, "cd"))
		ft_cd(command->next);
	else if (!ft_strcmp(command->content, "env"))
		ft_env(command->next);
	else if (!ft_strcmp(command->content, "export"))
		ft_export(command->next);
	else if (!ft_strcmp(command->content, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(command->content, "unset"))
		ft_unset(command->next);
	else if (!ft_strcmp(command->content, "exit"))
		ft_exit(command->next);
	return (0);
}

int	manage_tree(t_tree *root_tree, int std_in[2], int std_out[2])
{
	int		pid;
	int		i;
	t_type	type;
	t_list	*cmd;

	type = root_tree->type;
	i = 0;
	if (!root_tree->value)
		return (0);
	cmd = root_tree->value;
	if (!cmd)
		cmd = root_tree->left->value;
	if (check_if_command(cmd) && !std_in && !std_out)
		return (check_command(cmd, type, root_tree));
	pid = exe_cmd_pid(root_tree, std_in, std_out, type);
	if (pid == -1)
		return (-1);
	if (cmd && cmd->content)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (exe_waitpid(pid))
		return (-1);
	return (set_sig(0), 0);
}

int	manage_rdr(t_tree *tree, int std_in[2], int std_out[2])
{
	int		i;
	int		fd[2];
	t_tree	*tmp;

	tmp = tree;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (!tree->right->value)
		return (ft_printf(2,
				"minishell: syntax error near unexpected token\n"), -1);
	if (checking_rdr(tree, &tmp) == -1)
		return (-1);
	if (tree->right->value->next)
		ft_lstadd_back(&g_shell.args, tree->right->value->next);
	if (g_shell.args)
		ft_lstadd_back(&tmp->left->value, g_shell.args);
	exec(tmp->left, std_in, std_out, tree->type);
	i = stdio_res(g_shell.fd);
	if (i)
		return (-1);
	return (dup2(fd[0], STDIN_FILENO), dup2(fd[1], STDOUT_FILENO), 0);
}

int	exec(t_tree *tree, int std_in[2], int std_out[2], int i)
{
	if (!tree)
		return (-1);
	else if (check_if_rdr(tree) && i == 1)
		return (check_args(), manage_rdr(tree, NULL, NULL));
	else if (tree->type == PIPE)
		return (check_args(), manage_pipe(tree, std_in, std_out, i), 0);
	else if (tree->type != PIPE)
		return (check_args(), manage_tree(tree, std_in, std_out));
	return (-1);
}
