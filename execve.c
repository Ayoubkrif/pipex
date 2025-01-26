/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:11:14 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/26 12:24:58 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void	fall(char **dest)
{
	int	i;

	i = 0;
	if (dest == NULL)
		return ;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

void	exit_failure(char *message, char **to_free, int *pids_to_free)
{
	perror(message);
	fall(to_free);
	free(pids_to_free);
	exit(EXIT_FAILURE);
}

int	wait_all_pids(pid_t	*pids, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	return (status);
}

void	malloc_error(void)
{
	printf("malloc error\n");
}

char	**get_possible_paths(char **env)
{
	char	**possible_paths;
	int		i;

	i = 0;
	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	if (!*env || !ft_strnstr(*env, "PATH=", 5))
		return (NULL);
	possible_paths = ft_split(*env + 5, ':');
	if (!possible_paths)
		return (malloc_error(), NULL);
	while (possible_paths[i])
	{
		possible_paths[i] = ft_strjoin(possible_paths[i], "/", 1, 0);
		if (!possible_paths[i])
			return (malloc_error(), NULL);
		i++;
	}
	return (possible_paths);
}

char	**get_cmd(char *str, char **env)
{
	char	**cmd;
	char	*ret;
	char	**path;
	int		i;

	i = 0;
	cmd = ft_split(str, ' ');
	path = get_possible_paths(env);
	if (!path || !cmd)
		return (fall(path), fall(cmd), NULL);
	if (!access(*cmd, X_OK))
		return (fall(path), cmd);
	while (path[i])
	{
		ret = ft_strjoin(path[i], *cmd, 0, 0);
		if (!access(ret, X_OK))
		{
			free(*cmd);
			*cmd = ret;
			return (fall(path), cmd);
		}
		free(ret);
		i++;
	}
	(fall(path), path = NULL);
	exit_failure("access", cmd, NULL);
	return (NULL);
}

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
	if (n_cmd == 0)
	{
		data.in_fd = open(data.infile, O_RDONLY);
		if (data.in_fd == OPEN_FAILURE)
			perror("open");
	}
	else
		data.in_fd = data.last_pipe;
	if (n_cmd == data.n_argcmd - 2)
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
	while (i < data.n_argcmd - 1)
	{
		if (pipe(data.current_pipe) == PIPE_FAILURE)
			exit_failure("pipe", NULL, pids);
		pids[i] = fork();
		if (pids[i] == FORK_FAILURE)
			exit_failure("fork", NULL, pids);
		if (pids[i] == CHILD_PROCESS)
			(free(pids), child_process(data, argv[i], i, env));
		close(data.current_pipe[1]);
		if (i)
			close(data.last_pipe);
		data.last_pipe = data.current_pipe[0];
		i++;
	}
	close(data.last_pipe);
	return (0);
	return (wait_all_pids(pids, i));
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	pid_t	*pids;

	if (argc < 5)
		return (1);
	if (strcmp(argv[1], "here_doc"))
	{;}
	data.infile = argv[1];
	data.outfile = argv[argc - 1];
	data.n_argcmd = argc - 2;
	pids = malloc((argc - 2) * sizeof(pid_t));
	argv++;
	argv++;
	return (pipex(data, argv, env, pids));
}
