/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:11:14 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/21 15:57:31 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

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

static void	fall(char **dest)
{
	if (dest == NULL)
		return ;
	while (*dest)
	{
		printf("%s\n",*dest);
		free(*dest);
		dest++;
	}
	printf("%s\n",*dest);
	free(dest);
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
		ret = ft_strjoin(path[i], *cmd, 0, 1);
		if (!access(ret, X_OK))
		{
			*cmd = ret;
			return (fall(path), cmd);
		}
//		free(ret);
		i++;
	}
	//(fall(path), path = NULL);
	//(fall(cmd), cmd = NULL);
	return (perror("access"), NULL);
}

void	exec_cmd(char *str, char **env)
{
	char	**cmd;

	cmd = get_cmd(str, env);
	if (cmd)
	{
		while (*cmd)
		{
			printf("%s\n", *cmd);
			cmd++;
		}
	}
//	fall(cmd);
	exit(0);
	execve("/usr/bin/ls", cmd , env);
	perror("execve");
}

void	wait_all_pids(pid_t	*pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], 0, 0);
		i++;
	}
}

void	pipex(char **argv, char **env, int argc)
{
	t_var	pids;
	int		i;

	i = 2;
	while (i < argc - 1)
	{
		if (i < argc - 2)
			pipe(pids.pipe_fd);
		pids.pid[i - 2] = fork();
		if (pids.pid[i - 2] == 0)
		{
			exec_cmd(argv[i], env);
		}
		i++;
	}
	wait_all_pids(pids.pid, i - 2);
}
	/*if (pipe(pipe_fd) == -1)
		return (perror("pipe :"));
	file_fd[0] = open(argv[1], O_RDONLY);
	if (file_fd[0] == -1)
		return (perror("open infile:"));
	file_fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd[1] == -1)
		return (perror("open outfile:"));
	exec_cmd(argv[2], file_fd[0], pipe_fd[0], env);
	exec_cmd(argv[3], pipe_fd[1], file_fd[1], env);
	*/

int	main(int a, char **arg, char **e)
{
	if (!e || a < 5)
		return (1);
	pipex(arg, e, a);
	//pipex(arg, e, a);

	/*while (*e && !ft_strnstr(*e, "PATH=", 5))
		e++;
	if (!ft_strnstr(*e, "PATH=", 5))
		return (0);
	path = ft_split(*e + 5, ':');
	while (*path)
	{
		*path = ft_strjoin(*path, "/");
		cmd = ft_strjoin(*path, c[1]);
		printf("acces %d\n", access(cmd, X_OK));
		if (access(cmd, X_OK) == -1)
			perror("");
		printf("%s\n", cmd);
		path++;
	}
	printf("acces %d\n", access(c[1], X_OK));*/
}
