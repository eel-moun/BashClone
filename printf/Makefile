SRCS = ft_printf.c  ft_printfutils.c
NAME = libftprintf.a
INCLUDE = ft_printf.h
FLAGS = gcc -Wall -Wextra -Werror
OBJ = $(SRCS:.c=.o)

all: $(NAME)


$(NAME): $(OBJ)
	ar rc $@ $^

%.o : %.c $(INCLUDE)
	$(FLAGS) -c $<

clean:
	rm  -rf $(OBJ)

fclean: clean
	rm  -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
