/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:15:31 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 21:47:40 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	stdio_res(int stdio[2])
{
	int	fd[2];

	if (!stdio)
		return (0);
	fd[0] = dup2(stdio[0], STDIN_FILENO);
	fd[1] = dup2(stdio[1], STDOUT_FILENO);
	if (fd[0] == -1 || fd[1] == -1)
		return (perror("minishell"), -1);
	return (0);
}

int	exe_waitpid(int pid)
{
	pid_t	wait;
	int		status;

	wait = waitpid(pid, &status, 0);
	if (wait == -1)
		return (wait);
	if (WIFEXITED(status))
		g_shell.exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_shell.exit = WTERMSIG(status);
	else
		g_shell.exit = 1;
	return (0);
}

void	close_pipe(int std[2])
{
	if (!std)
		return ;
	close(std[0]);
	close(std[1]);
}

static void	set_fork_pipes(int std_in[2], int std_out[2])
{
	if (std_in && dup2(std_in[0], 0) == -1)
	{
		perror("minishell");
		exit(1);
	}
	close_pipe(std_in);
	if (std_out && dup2(std_out[1], 1) == -1)
	{
		perror("minishell");
		exit(1);
	}
	close_pipe(std_out);
}

int	set_fork(int std_in[2], int std_out[2])
{
	int	pid;

	pid = fork();
	if (pid == 0)
		set_fork_pipes(std_in, std_out);
	else if (pid == -1)
		perror("minishell");
	else
		close_pipe(std_in);
	return (pid);
}
