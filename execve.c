/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:11:14 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/19 14:39:36 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_possible_paths(char **env)
{
	char	**possible_paths;

	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	if (!*env || !ft_strnstr(*env, "PATH=", 5))
		return (NULL);
	possible_paths = ft_split(*env + 5, ':');
	if (!possible_paths)
		return (NULL);
	return (possible_paths);
}

char	**get_cmd(char *str)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(str, ' ');
	if (!cmd)
		return (NULL);
	if (*cmd)
		*cmd = ft_strjoin("/", *cmd);
	return (cmd);
}

char	**check_cmd(char *str, char **env)
{
	char	**cmd;
	char	**path;
	int		i;

	i = 0;
	path = get_possible_paths(env);
	cmd = get_cmd(str);
	if (!path)
		return (NULL);
	if (!access(*cmd, X_OK))
		return (cmd);
	while (cmd[i])
	{
		cmd[i] = ft_strjoin(*path, cmd[i]);
		if (!access(cmd[i], X_OK))
			return (cmd);
		path++;
		i++;
	}
	return (perror("access"), NULL);
}

void	exec_cmd(char *str, int fd_in, int fd_out, char **env)
{
	char	**cmd;

	cmd = check_cmd(str, env);
	if (!cmd)
		return ;
	execve(*cmd, cmd + 1, env);
}

void	pipex(char **argv, char **env, int argc)
{
	t_var	pids;
	// init pid
	int		pipe_fd[2];
	int		file_fd[2];
	int		i;

	
	i = 2;
	while (i < argc - 1)
	{
		if (i < argc - 2)
			pipe(pipe_fd);
		// pipe error
		pids.pid[i - 2] = fork();
		// fork error
		if (pids.pid[i - 2] == 0)
		{
			exec_cmd(argv[i], pids.in_fd, pids.out_fd, env);
		}
		i++;
	}
	//wait_all_pids(pid);
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
