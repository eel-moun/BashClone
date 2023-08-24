/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:07:16 by btaha             #+#    #+#             */
/*   Updated: 2023/01/14 21:36:00 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include "token.h"
# include "lexer.h"
# include "parsing.h"

typedef struct s_shell
{
	t_list	*env;
	int		exit;
	int		exec;
	int		error;
	int		fd[2];
	t_list	*args;
}	t_shell;

extern t_shell	g_shell;
typedef struct s_env
{
	char	*name;
	char	*value;
	int		print;
}	t_env;

typedef void	(*t_delfn)(void *);

int		ft_echo(t_list *args, t_type type);
void	check_args(void);
int		check_pipe(t_tree *tree);
void	free_tree_node(t_tree *tree);
void	free_tree(t_tree **parse);
void	advance(t_tree **temp);
int		checking_rdr(t_tree	*tree, t_tree **tmp);
int		stdio_dup2(t_type type, int fd);
int		check_left(t_tree *tree, int n);
int		stdio_res(int stdio[2]);
int		open_file(char *file, t_type type);
int		check_rdr_io(t_tree *tree);
int		check_rdr_i(t_tree *tmp, int n, t_tree **temp, int *j);
int		manage_rdr(t_tree *tree, int std_in[2], int std_out[2]);
int		check_rdr_o(t_tree *tmp, int n, t_tree **temp, int *j);
char	*filename(char *str);
int		check_rdr_oi(t_tree *tree);
int		check_rdr(t_tree *tree, int stdio[2], char *file);
int		exec_path(char *path_env, char *path, t_list *cmd);
int		exe_cmd_pid(t_tree *tree, int std_in[2], int std_out[2], t_type type);
int		exe_exec(char *path, t_list *cmd);
int		event(void);
void	handler(int sig);
int		exec_ve(t_list *cmd);
int		check_if_command(t_list *command);
int		exec_cmd(t_tree *tree, t_list *command, t_type type);
int		check_if_rdr(t_tree *tree);
int		set_fork(int std_in[2], int std_out[2]);
int		exe_waitpid(int pid);
void	close_pipe(int std[2]);
int		exec(t_tree *tree, int std_in[2], int std_out[2], int i);
int		manage_pipe(t_tree *tree, int std_in[2], int std_out[2], int r);
void	free_env(t_env *env);
void	free_str(char **str);
char	**get_env(void);
int		set_fork(int std_i[2], int std_o[2]);
int		exe_waitpid(int pid);
void	close_pipe(int std[2]);
int		set_sig(int catch_signals);
t_env	*set_var(char *name, char *value);
t_list	*find_name(t_list *env, char *name);
char	*ft_getenv(char *name);
void	free_env(t_env *env);
int		ft_unset(t_list *args);
int		update_env(t_env *env, char *value, int print);
int		add_env(char *name, char *value, int print);
int		set_env(char *name, char *value, int print);
int		ft_pwd(void);
int		ft_cd(t_list *directorie);
int		ft_env(t_list *args);
int		ft_export(t_list *var);
int		ft_exit(t_list *args);
int		init_env(char *envp[]);
#endif