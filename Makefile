NAME = pipex
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
LIBFT = libft.a  # Si vous avez une libft

SRCS = execve.c get_next_line.c get_next_line_utils.c
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
	"sleep 10" "sleep 5" "ls" \
	outfile
	cat outfile
	echo $$?

vtest: all
	rm -f outfile
	@valgrind --trace-children=yes --track-fds=yes ./pipex infile \
	"sleep 10" "sleep 5" "ls" ""\
	outfile 2>&1 | grep -E "errors from|heap|HEAP|open|Command|blocks" \
	| GREP_COLORS='mt=1;4;32' grep --color=always -E "HEAP SUMMARY|$$" \
	| GREP_COLORS='mt=1;4;31' grep --color=always -E "ERROR SUMMARY|$$" \
	| GREP_COLORS='mt=1;4;33' grep --color=always -E "FILE DESCRIPTORS|$$" \
	| GREP_COLORS='mt=1;4;36' grep --color=always -E "==.....==|$$" \
	| GREP_COLORS='mt=1;5;35' grep --color=always -E "All heap blocks were freed -- no leaks are possible|$$"
	@cat outfile
	@echo "exit code :"
	@echo $$?

re: fclean all

.PHONY: all clean fclean re test vtest

