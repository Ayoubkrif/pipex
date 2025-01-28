/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:02:36 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/28 10:05:57 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fall(char **dest)
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
