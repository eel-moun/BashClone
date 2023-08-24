# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btaha <btaha@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 14:11:31 by btaha             #+#    #+#              #
#    Updated: 2023/01/14 22:13:28 by btaha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = minishell.c free_utils.c rdr_utils3.c lexer.c rdr.c lexer_parse1.c rdr_utils2.c fork_utils.c redir_utils.c signals.c pipe_utils.c exec_utils2.c exec_utils.c lexer_parse2.c token.c parsing_into_ast.c parsing_utils.c exec.c trees1.c trees2.c env_utils.c export_utils.c ./commands/cd.c ./commands/echo.c ./commands/env.c ./commands/exit.c ./commands/export.c ./commands/pwd.c ./commands/unset.c

NAME = minishell

CC = cc

CFLAGS = -O2 -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -Wall -Wextra -Werror -MMD -fsanitize=address

DEP = $(SRC:.c=.d)

all: $(NAME)

$(NAME): $(SRC) libft/libft.a printf/libftprintf.a
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) libft/libft.a printf/libftprintf.a -lreadline 

.PHONY: all clean fclean re

libft/libft.a:
	make -C Libft all

printf/libftprintf.a:
	make -C Printf all

clean:
	rm -rf $(DEP)
	make -C Libft clean
	make -C Printf clean

fclean: clean
	rm -rf $(NAME) $(DEP)
	make -C Libft fclean
	make -C Printf fclean

re:	fclean all
-include $(DEP)
