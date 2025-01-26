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
# include "get_next_line.h"

typedef struct s_hdoc
{
	char	*limiter;
	int		hdoc_pipe[2];
}	t_hdoc;

typedef struct s_pipex
{
	char			*infile;
	char			*outfile;
	int				hdoc;
	int				current_pipe[2];
	int				last_pipe;
	int				in_fd;
	int				out_fd;
	int				n_argcmd;
}	t_pipex;

# define FORK_FAILURE -1
# define PIPE_FAILURE -1
# define OPEN_FAILURE -1
# define CHILD_PROCESS 0
#endif
