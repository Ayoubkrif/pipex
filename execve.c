/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:11:14 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/22 19:54:04 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
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
	(fall(cmd), cmd = NULL);
	return (perror("access"), NULL);
}

void	exec_cmd(char *str, char **env)
{
	char	**cmd;

	cmd = get_cmd(str, env);
	execve(*cmd, cmd, env);
	perror("execve");
	fall(cmd);
	exit(0);
}

void	child_process(t_pipex data, char *argv, int n_cmd, char **env)
{
	close(data.pipe_fd[0]);
	if (n_cmd == 0) // sortie vers le pipe entree est le data.file
	{
		data.infile_fd = open(data.infile, O_RDONLY);
		if (data.infile_fd == -1)
			perror("open");
		dup2(data.infile_fd, STDIN_FILENO);
		close(data.infile_fd);
        dup2(data.pipe_fd[1], STDOUT_FILENO);
		close(data.pipe_fd[1]);
	}
	if (n_cmd == data.n_argcmd)
	{
        dup2(data.last_pipe_fd, STDIN_FILENO);
		close(data.last_pipe_fd);
		data.outfile_fd = open(data.outfile, O_WRONLY + O_CREAT + O_TRUNC, 0644);
		if (data.outfile_fd == -1)
			perror("open");
		dup2(data.outfile_fd, STDOUT_FILENO);
		close(data.outfile_fd);
	}
	else
	{
		dup2(data.last_pipe_fd, STDIN_FILENO);
		close(data.last_pipe_fd);
        dup2(data.pipe_fd[1], STDOUT_FILENO);
		close(data.pipe_fd[1]);
	}
	exec_cmd(argv, env);
}

int	pipex(t_pipex data, char **argv, char **env)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		data.pid[i] = fork();
		pipe(data.pipe_fd);
		if (data.pid[i])
			child_process(data, argv[i], i + 1, env);
		close(data.last_pipe_fd);
		data.last_pipe_fd = data.pipe_fd[0];
		close(data.pipe_fd[1]);
		i++;
	}
	return (wait_all_pids(data.pid, i));
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;

	argv++;
	if (argc < 5)
		return (1);
	data.infile = argv[0];
	data.outfile = argv[argc - 2];
	data.n_argcmd = argc - 2;
	data.pid = malloc((argc - 2) * sizeof(pid_t));
	argv++;
	return (pipex(data, argv, env));
}
