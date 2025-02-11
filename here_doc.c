/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:11:04 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/28 17:43:09 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	strcmp_end_newline(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\n' || *s2 == 0)
		return (1);
	return (0);
}

void	prompt_here_doc(t_pipex *data)
{
	char	*s;

	close(data->current_pipe[0]);
	while (TRUE)
	{
		write(1, "pipe heredoc> ", 14);
		s = get_next_line(0);
		if (!s)
			break ;
		if (strcmp_end_newline(s, data->infile))
		{
			free(s);
			break ;
		}
		write(data->current_pipe[1], s, ft_strlen(s));
		free(s);
	}
	close(data->current_pipe[1]);
	exit(EXIT_SUCCESS);
}

void	here_doc_process(t_pipex *data, pid_t *pids)
{
	pid_t	pid;

	if (data->here_doc == 0)
		return ;
	if (pipe(data->current_pipe) == PIPE_FAILURE)
	{
		free(pids);
		exit_failure("pipe");
	}
	pid = fork();
	if (pid == FORK_FAILURE)
	{
		free(pids);
		close(data->current_pipe[0]);
		close(data->current_pipe[1]);
		exit_failure("fork");
	}
	if (pid == CHILD_PROCESS)
	{
		free(pids);
		prompt_here_doc(data);
	}
	close(data->current_pipe[1]);
	data->last_pipe = data->current_pipe[0];
	waitpid(pid, NULL, 0);
}
