/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:04:06 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/28 10:13:16 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"

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

void	fall(char **dest);
void	exit_failure(char *message, char **to_free, int *pids_to_free);
int		wait_all_pids(pid_t	*pids, int n);
void	malloc_error(void);

char	**get_possible_paths(char **env);
char	**get_cmd(char *str, char **env);

int		strcmp_end_newline(char *s1, char *s2);
void	prompt_here_doc(t_pipex *data);
void	here_doc_process(t_pipex *data, pid_t *pids);

#endif
