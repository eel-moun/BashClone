/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:38:30 by btaha             #+#    #+#             */
/*   Updated: 2023/01/13 21:10:39 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	sig_int_handler(int sig)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	if (g_shell.exec)
		return ;
	rl_on_new_line();
	rl_redisplay();
	g_shell.exit = 128 + sig;
}

static void	sig_quit_handler(int sig)
{
	if (!g_shell.exec)
		return ;
	rl_replace_line("", 0);
	ft_printf(1, "Quit: %d\n", sig);
}

int	set_sig(int catch_signals)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (catch_signals)
		rl_catch_signals = 0;
	return (0);
}

int	event(void)
{
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_shell.exec = -1;
		rl_done = 1;
	}
}
