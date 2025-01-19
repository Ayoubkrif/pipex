/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:41:44 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/13 07:59:25 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_join(char const *s1, char const *s2, char **r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		(*r)[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		(*r)[i + j] = s2[j];
		j++;
	}
	(*r)[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	r = (char *)malloc(sizeof(char) * (1 + i + j));
	if (!r)
		return (NULL);
	ft_join(s1, s2, &r);
	return (r);
}
