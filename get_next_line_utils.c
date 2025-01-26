/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:16:36 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/26 21:47:53 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strjoinf(char *s1, char const *s2)
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
	{
		free(s1);
		return (NULL);
	}
	ft_join(s1, s2, &r);
	free(s1);
	return (r);
}

char	*ft_substrf(char *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*r;
	unsigned int	smax;

	i = 0;
	smax = 0;
	while (s[smax])
		smax++;
	while (smax >= start && (s + start)[i] && i < len)
		i++;
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (smax >= start && (s + start)[i] && i < len)
	{
		r[i] = (s + start)[i];
		i++;
	}
	r[i] = '\0';
	free(s);
	return (r);
}

char	*ft_strchrf(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)(s + i));
	return (NULL);
}

void	*ft_callocf(size_t nmemb, size_t size)
{
	void	*rep;
	size_t	i;

	if (nmemb && size > 2147483647 / nmemb)
		return (NULL);
	i = 0;
	rep = malloc(nmemb * size);
	if (!rep)
		return (NULL);
	while (i < nmemb * size)
		((unsigned char *)rep)[i++] = 0;
	return (rep);
}
