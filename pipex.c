/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:11:14 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/28 10:12:52 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	exec_cmd(char *str, char **env)
{
	char	**cmd;

	cmd = get_cmd(str, env);
	execve(*cmd, cmd, env);
	exit_failure("execve", cmd, NULL);
}

void	child_process(t_pipex data, char *argv, int n_cmd, char **env)
{
	close(data.current_pipe[0]);
	if (n_cmd == 0 && data.hdoc == 0)
	{
		data.in_fd = open(data.infile, O_RDONLY);
		if (data.in_fd == OPEN_FAILURE)
			perror("open");
	}
	else
		data.in_fd = data.last_pipe;
	if (n_cmd == data.n_argcmd - 1)
	{
		close(data.current_pipe[1]);
		data.out_fd = open(data.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data.out_fd == OPEN_FAILURE)
			perror("open");
	}
	else
		data.out_fd = data.current_pipe[1];
	dup2(data.in_fd, STDIN_FILENO);
	dup2(data.out_fd, STDOUT_FILENO);
	close(data.in_fd);
	close(data.out_fd);
	exec_cmd(argv, env);
}

int	pipex(t_pipex data, char **argv, char **env, int *pids)
{
	int	i;

	i = 0;
	here_doc_process(&data, pids);
	while (i < data.n_argcmd)
	{
		if (pipe(data.current_pipe) == PIPE_FAILURE)
			exit_failure("pipe", NULL, pids);
		pids[i] = fork();
		if (pids[i] == FORK_FAILURE)
			exit_failure("fork", NULL, pids);
		if (pids[i] == CHILD_PROCESS)
			(free(pids), child_process(data, argv[i], i, env));
		close(data.current_pipe[1]);
		if (i || data.hdoc)
			close(data.last_pipe);
		data.last_pipe = data.current_pipe[0];
		i++;
	}
	close(data.last_pipe);
	return (wait_all_pids(pids, i));
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	pid_t	*pids;

	if (argc < 5)
		return (1);
	data.hdoc = 0;
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
			return (1);
		data.hdoc = 1;
		argv++;
		argc--;
	}
	data.infile = argv[1];
	data.outfile = argv[argc - 1];
	data.n_argcmd = argc - 3;
	pids = malloc((data.n_argcmd) * sizeof(pid_t));
	argv = argv + 2;
	return (pipex(data, argv, env, pids));
}
