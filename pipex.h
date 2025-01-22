#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"

typedef struct s_pipex{
	pid_t	*pid;
	char	*infile;
	char	*outfile;
	int		pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		last_pipe_fd;
	int		in_fd;
	int		out_fd;
	int		n_argcmd;
}t_pipex;

#endif
