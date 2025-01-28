/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:08:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/28 10:09:00 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_possible_paths(char **env)
{
	char	**possible_paths;
	char	*temp;
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
		temp = ft_strjoin(possible_paths[i], "/", 1, 0);
		if (!temp)
			return (malloc_error(), NULL);
		possible_paths[i] = temp;
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
