NAME = pipex
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
LIBFT = libft.a  # Si vous avez une libft

SRCS = execve.c
OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	make -C libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L. libft/$(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

test: all
	rm -f outfile
	cat > infile
	@./pipex infile \
	cat cat \
	outfile
	cat outfile
	echo $$?

vtest: all
	rm -f outfile
	cat > infile
	@valgrind --trace-children=yes --track-fds=yes ./pipex infile \
	cat cat \
	outfile 2>&1 | grep -E "errors from|heap|HEAP|open"
	@echo 
	@cat outfile
	@echo "exit code :"
	@echo $$?

re: fclean all

.PHONY: all clean fclean re test vtest

