/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:12:36 by aykrifa           #+#    #+#             */
/*   Updated: 2024/11/16 12:04:16 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include<bsd/string.h>
#include<ctype.h>
#include <string.h>

/*strncmp strncpy memcmp memmove strnstr strlcat strtrim split strjoin substr itoa
  toupper tolower isprint isidigt isalnum isacii isalpha strchr strrchr strlen atoi
  bzero memset putendl_fd putstr_fd putnbr_fd putchar_fd*/
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
	if (mode == 0)
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
	if (mode == 2)
	{	
		if (s1)
                        free(*s1);
                if (s2)
                       free(*s2);
                if (s1b)
                        free(*s1b);
                if (s2b)
                        free(*s2b);
	}
}
/* strncmp, strlcat, strlcpy, memcpy, memmove, strnstr,-lbsd */
int	main(int a, char **c)
{
	char	*s1;
	char	*s2;
	char	*s1b;
	char	*s2b;
	int	i;
	char	*s;
	char	**p;
	int	j;

	Buffinit(1, c[2],c[3],&s1, &s2, &s1b, &s2b);
	if (strstr(c[1], "strncmp") && a >= 5)
	{
		printf("Strncmp : \n");
		printf("My strncmp : %i\n", ft_strncmp(s1, s2, ft_atoi(c[4])));
		printf("Real One   : %i\n", strncmp(s1, s2, ft_atoi(c[4])));
	}
	if (strstr(c[1], "strlcpy") && a >= 5)
	{
		printf("====================\nStrlcpy : \n");
		printf("My strlcpy : %lu\ndst        :%s\nsrc        :%s\n", ft_strlcpy(s2, s1, ft_atoi(c[4])), s2, s1);
		printf("Real One   : %lu\ndst        :%s\nsrc        :%s\n", strlcpy(s2, s1, ft_atoi(c[4])), s2, s1);
	}
	if (strstr(c[1], "memcmp") && a >= 5)
        {
                Buffinit(0, c[2],c[3],&s1, &s2, &s1b, &s2b);
                printf("====================\nMemcmp : \n");
                printf("My memcmp  :%i\n", (ft_memcmp((void *)s1, (void *)s2, (size_t)ft_atoi(c[4]))));
                printf("Real One   :%i\n", (memcmp((void *)s1, (void *)s2, (size_t)ft_atoi(c[4]))));
        }
	if (strstr(c[1], "memcpy") && a >= 5)
	{
		Buffinit(0, c[2],c[3],&s1, &s2, &s1b, &s2b);
		printf("====================\nMemcpy : \n");
		printf("My memcpy  :%s\n", ((char *)ft_memcpy((void *)s1, (void *)s2, (size_t)ft_atoi(c[4]))));
		printf("Real One   :%s\n", ((char *)memcpy((void *)s1, (void *)s2, (size_t)ft_atoi(c[4]))));
	}
	if (strstr(c[1], "memmove") && a >= 5)
	{
		printf("====================\nMemmove :\n");
		Buffinit(0, c[2],c[3],&s1, &s2, &s1b, &s2b);
		printf("My Memmove :%s\n", (char *)ft_memmove((void *)s1, (void *)s2, (size_t)ft_atoi(c[4])));
		printf("Real One   :%s\n", (char *)memmove((void *)s1, (void *)s2, (size_t)ft_atoi(c[4])));
	}
	if (strstr(c[1],"strnstr") && a >= 5)
	{
		Buffinit(0, c[2],c[3],&s1, &s2, NULL, NULL);
		printf("====================\nStrnstr : \n");
		printf("My strnstr :%s\n", ft_strnstr(s1, s2, (size_t)ft_atoi(c[4])));
		printf("Real One   :%s\n", strnstr(s1, s2, (size_t)ft_atoi(c[4])));
	}
	if (strstr(c[1], "strlcat") && a >= 5)
	{

		Buffinit(0, c[2],c[3],&s1, &s2, NULL, NULL);
		printf("====================\nStrlcat : \n");
		printf("My strlcat :%lu\ndst        :%s\nsrc        :%s\n", ft_strlcat(s1, s2, (size_t)ft_atoi(c[4])), s2, s1);
		Buffinit(0, c[2],c[3],&s1, &s2, NULL, NULL);
		printf("Real One   :%lu\ndst        :%s\nsrc        :%s\n", strlcat(s1, s2, (size_t)ft_atoi(c[4])), s2, s1);
	}
	if (strstr(c[1],"strtrim") && a >= 4)
	{
		s = ft_strtrim(s1, s2); 
		printf("====================\nStrtrim : \n");
		printf("My strtrim :%s\n", s);
		free(s);
	}
	if (strstr(c[1], "split") && a >= 4)
	{
		p = ft_split(s1, c[3][0]);
		printf("====================\nSplit : \n");
		i = 0;
		while (p[i])
		{
			ft_putstr_fd(p[i], 1);
			ft_putchar_fd('\n', 1);
			i++;
		}
		free(p);
	}
	if (strstr(c[1], "strjoin") && a >= 4)
	{
		printf("====================\nStrjoin : \n");
		s = ft_strjoin(s1, s2);
		printf("My strjoin :%s\n", s);
		free(s);
	}
	if (strstr(c[1], "substr") && a >= 5)
	{
		s = ft_substr(s1 , ft_atoi(s2), ft_atoi(c[4]));
		printf("====================\nSubstr : \nMy substr :");
		ft_putstr_fd(s, 1);
		ft_putchar_fd('\n', 1);
		free(s);
	}
	if (strstr(c[1], "itoa") && a >= 3)
	{
		printf("====================\nItoa:\n");
		i = 0;
		while(i + 3 <= a)
		{
			s = ft_itoa(ft_atoi(c[i + 3]));
			printf("itoa %i : %s\n",i + 1, s);
			free(s);
			i++;
		}
	}
/*
	if (strstr(c[1], "strmapi") && a >= 3)
	{
		printf("====================\nStrmapi:\n");
	}
	if (strstr(c[1], "striteri") && a >= 3)
	{
		printf("====================\nStriteri:\n");
	}
*/
	if (strstr(c[1], "toupper") && a >= 3)
	{
		printf("====================\nToupper:\n");
                
		i = 0;
                Buffinit(0, c[2],c[3],&s1, NULL, NULL, NULL);
                while (s1[i])
                {
                        s1[i] = ft_toupper(s1[i]);
			i++;
                }
		printf("My toupper :%s\n", s1);
                Buffinit(0, c[2],c[3],&s1, NULL, NULL, NULL);
		i = 0;
                while (s1[i])
                {
                        s1[i] = toupper(s1[i]);
                        i++;
                }
                printf("Real One   :%s\n",s1);
	}
	if (strstr(c[1], "tolower") && a >= 3)
	{
		printf("====================\nTolower:\n");
		i = 0;
                Buffinit(0, c[2],c[3],&s1, NULL, NULL, NULL);
                while (s1[i])
                {
                        s1[i] = ft_tolower(s1[i]);
                        i++;
                }
                printf("My tolower :%s\n", s1);
                Buffinit(0, c[2],c[3],&s1, NULL, NULL, NULL);
                i = 0;
                while (s1[i])
                {
                        s1[i] = tolower(s1[i]);
                        i++;
                }
                printf("Real One   :%s\n",s1);
	}
	if (strstr(c[1], "isprint") && a >= 3)
	{
		printf("====================\nIsprint:\n");
                i = 0;
                while (c[2][i])
                {
                        printf("My isprint :%i\n", ft_isprint(c[2][i]));
                        printf("Real One   :%i\n", isprint(c[2][i]));
                        i++;
                }
	}
	if (strstr(c[1], "isdigit") && a >= 3)
	{
		printf("====================\nIsdigit:\n");
                i = 0;
                while (c[2][i])
                {
                        printf("My isdigit :%i\n", ft_isdigit(c[2][i]));
                        printf("Real One   :%i\n", isdigit(c[2][i]));
                        i++;
                }
	}
	if (strstr(c[1], "isalnum") && a >= 3)
	{
		printf("====================\nIsalnum:\n");
                i = 0;
                while (c[2][i])
                {
                        printf("My isalnum :%i\n", ft_isalnum(c[2][i]));
                        printf("Real One   :%i\n", isalnum(c[2][i]));
                        i++;
                }
	}
	if (strstr(c[1], "isascii") && a >= 3)
	{
		printf("====================\nIsascii:\n");
                i = 0;
                while (c[2][i])
                {
			printf("My isascii :%i\n", ft_isascii(c[2][i]));
                	printf("Real One   :%i\n", isascii(c[2][i]));
			i++;
                }
	}
	if (strstr(c[1], "isalpha") && a >= 3)
	{
		printf("====================\nIsalpha:\n");
                i = 0;
                while (c[2][i])
                {
                        printf("My isalpha :%i\n", ft_isalpha(c[2][i]));
                        printf("Real One   :%i\n", isalpha(c[2][i]));
                        i++;
                }
	}
	if (strstr(c[1], "strchr") && a >= 4)
	{
		printf("====================\nStrchr:\n");
		printf("My strchr  :%s\n", ft_strchr(s1,atoi(s2)));
                printf("Real One   :%s\n", strchr(s1, atoi(s2)));
	}
	if (strstr(c[1], "strrchr") && a >= 4)
	{
		printf("====================\nStrrchr:\n");
                printf("My strrchr  :%s\n", ft_strrchr(s1,atoi(s2)));
                printf("Real One   :%s\n", strrchr(s1, atoi(s2)));

	}
	if (strstr(c[1], "strlen") && a >= 3)
	{
		printf("====================\nStrlen:\n");
		 i = 0;
		while(i + 3 <= a)
		{
                        printf("my len %i : %i\n",i + 1, (int)ft_strlen(c[i + 2]));
			printf("Real one  : %i\n", (int)strlen(c[i + 2]));
                        i++;
                }
	}
	if (strstr(c[1], "atoi") && a >= 3)
	{
		printf("====================\nAtoi:\n");
		i = 0;
		while (i + 3 <= a)
		{
			printf("My atoi  %i: %i\n",i + 1, ft_atoi(c[i + 2]));
                        printf("Real one  : %i\n", atoi(c[i + 2]));
			i++;
		}
	}/*
	if (strstr(c[1], "bzero") && a >= 3)
	{
		printf("====================\nBzero:\n");
		Buffinit(0, c[2],c[3],&s1, &s2, NULL, NULL);
		printf("My Bzero   :%s\n", (char *)ft_bzero(s1, (size_t)ft_atoi(c[4])));
                Buffinit(0, c[2],c[3],&s1, NULL, NULL, NULL);
		printf("Real One   :%s\n", (char *)bzero(s1, (size_t)ft_atoi(c[4])));
	}*/
	if (strstr(c[1], "memset") && a >= 4)
	{
		printf("====================\nMemset:\n");
                Buffinit(0, c[2],c[3],&s1, NULL, NULL, NULL);
		printf("My memset :%s\n", (char *)ft_memset(s1, atoi(c[3]), (size_t)ft_atoi(c[4])));
                Buffinit(0, c[2],c[3],&s1, NULL, NULL, NULL);
                printf("Real One   :%s\n", (char *)memset(s1,atoi(c[3]) ,(size_t)ft_atoi(c[4])));

	}
	if (strstr(c[1], "putendl_fd") && a >= 3)
	{
		printf("====================\nPutendl_fd:\n");
                i = 0;
                while (i + 3 <= a)
                {
                	printf("str %i :",i + 1);
                        ft_putendl_fd(c[i + 2], 1);       
			printf("\n");
                }
	}
	if (strstr(c[1], "putstr_fd") && a >= 3)
	{
		printf("====================\nPutstr_fd:\n");
                i = 0;
                while (i + 3 <= a)
                {
                        printf("str %i :",i + 1);
                        ft_putstr_fd(c[i + 2], 1);
			printf("\n");
                        i++;
                }
	}
	if (strstr(c[1], "putnbr_fd") && a >= 3)
	{
		printf("====================\nPutnbr_fd:\n");
                i = 0;
                while (i + 3 <= a)
                {
			printf("nbr %i :",i + 1);
			ft_putnbr_fd(atoi(c[i + 2]), 1);
			printf("\n");
			i++;
                }
	}
	if (strstr(c[1], "putchar_fd") && a >= 3)
        {
                printf("====================\nPutchar_fd:\n");
                i = 0;
		int y = 0;
                while (i + 3 <= a)
                {
                        while (c[i + 3][j])
			{
				printf("char %i :",i + 1);
                	        ft_putchar_fd(c[i + 2][j], 1);
                	        printf("\n");
                        	j++;
			}
			i++;
                }
        }
	free(s1);
	free(s2);
	free(s1b);
	free(s2b);
	return (0);
}

