#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include "libft/libft.h"

typedef struct s_var{
	pid_t	pid[100];
	int		pipe_fd;
	int		in_fd;
	int		out_fd;
}t_var;

#endif
