NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a  # Si vous avez une libft

SRCS = execve.c
OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

libft :
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L. libft/$(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

