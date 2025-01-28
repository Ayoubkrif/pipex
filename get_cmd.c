/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:08:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/28 11:34:35 by aykrifa          ###   ########.fr       */
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

char	**access_cmd(char	**path, char **cmd)
{
	int		i;
	char	*ret;

	i = 0;
	while (path[i])
	{
		ret = ft_strjoin(path[i], *cmd, 0, 0);
		if (!ret)
			return (malloc_error(), fall(cmd), NULL);
		if (!access(ret, X_OK))
		{
			free(*cmd);
			*cmd = ret;
			return (fall(path), cmd);
		}
		free(ret);
		i++;
	}
	fall(cmd);
	return (NULL);
}

char	**get_cmd(char *str, char **env)
{
	char	**cmd;
	char	**path;

	cmd = ft_split(str, ' ');
	if (!cmd)
		return (malloc_error(), NULL);
	path = get_possible_paths(env);
	if (!path)
		return (fall(cmd), NULL);
	if (!access(*cmd, X_OK))
		return (fall(path), cmd);
	cmd = access_cmd(path, cmd);
	if (cmd)
		return (cmd);
	fall(path);
	return (NULL);
}
