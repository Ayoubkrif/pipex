/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:12:36 by aykrifa           #+#    #+#             */
/*   Updated: 2024/11/14 09:42:03 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <bsd/string.h>
#include <string.h>

/* strlcat, strlcpy, memcpy, memmove, strnstr, */

void	Buffinit(int mode, char *i1, char *i2, char **s1, char **s2, char **s1b, char **s2b)
{
	if (mode == 1)
	{
		if (s1)
			*s1 = ft_strdup(i1);
		if (s2)
			*s2 = ft_strdup(i2);
		if (s1b)
			*s1b = ft_strdup(i1);
		if (s2b)
			*s2b = ft_strdup(i2);
	}
	else
	{
		if (s1)
			*s1 = strcpy(*s1, i1);
		if (s2)
			*s2 = strcpy(*s2, i2);
		if (s1b)
			*s1b = strcpy(*s1b, i1);
		if (s2b)
			*s2b = strcpy(*s2b, i2);
	}
}
/* strncmp, strlcat, strlcpy, memcpy, memmove, strnstr,-lbsd */
int	main(int a, char **c)
{
	int	count = ft_atoi(c[4]);
	char	*s1;
	char	*s2;
	char	*s1b;
	char	*s2b;

	Buffinit(1, c[2],c[3],&s1, &s2, &s1b, &s2b);
	if (strstr(c[1], "strncmp") && a >= 5)
	{
		printf("Strncmp : \n");
		printf("My strncmp : %d\n", ft_strncmp(s1, s2, count));
		printf("Real One   : %d\n", strncmp(s1, s2, count));
	}
	if (strstr(c[1], "strlcpy") && a >= 5)
	{
		printf("====================\nStrlcpy : \n");
		printf("My strlcat : %lu\ndst        :%s\nsrc        :%s\n", ft_strlcpy(s2, s1, count), s2, s1);
		printf("Real One   : %lu\ndst        :%s\nsrc        :%s\n", strlcpy(s2, s1, count), s2, s1);
	}
	Buffinit(0, c[2],c[3],&s1, &s2, &s1b, &s2b);
	if (strstr(c[1], "memcmp") && a >= 5)
	{
		printf("====================\nMemcmp : \n");
		printf("My memcmp  :%s\n", (char *)ft_memcpy((void *)s1, (void *)s2, (size_t)count));
		printf("Real One   :%s\n", (char *)memcpy((void *)s1, (void *)s2, (size_t)count));
	}
	if (strstr(c[1], "memmove") && a >= 5)
	{
		printf("====================\nMemmove :\n");
		printf("My strncmp :%s\n", (char *)ft_memmove((void *)s1, (void *)s2, (size_t)count));
		printf("Real One   :%s\n", (char *)memmove((void *)s1, (void *)s2, (size_t)count));
	}
	Buffinit(0, c[2],c[3],&s1, &s2, NULL, NULL);
	if (strstr(c[1],"strnstr") && a >= 4)
	{
		printf("====================\nStrnstr : \n");
		printf("My strnstr :%s\n", ft_strnstr(s1, s2, (size_t)count));
		printf("Real One   :%s\n", strnstr(s1, s2, (size_t)count));
	}
	return (0);
}
