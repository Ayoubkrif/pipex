/*
int     main(void)
{
        void    *r;

        //r = ft_calloc(-5, -5);
        r = calloc(-5,-5);
        if (!r)
                return  (1);
        free(r);
        return (0);
}
*/
/*
void	ft_putnbr(size_t nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{	
		nb = -nb;
		ft_putchar('-');
	}	
	if (nb > 9)
	{
		ft_putnbr((nb / 10));
	}
	ft_putchar((nb % 10) + 48);
}

size_t	main(size_t a, char **c)
{
	size_t	i;
	char	**rep;
	const char *s;

	(void)a;
	i = 0;
	s = ft_strdup(c[1]);
	ft_putnbr(count_words(s,c[2][0]));
	ft_putstr(" mots \n");
	rep = ft_split(s,c[2][0]);
	if (rep == NULL)
		return (1);
	while (i < count_words(c[1],c[2][0]))
	{
		ft_putstr("->");
		ft_putstr(rep[i]);
		ft_putchar('\n');
		i++;
	}
	if (rep[i] == 0)
		ft_putstr("FIN\n");
	freeall(&rep, i);
	free((char *)s);
}*/
/*
SUBSTR
int	main(int a, char **c)
{
	char *r;
	r = ft_substr("hola", 4294967295, 0);
	printf("%s\n", r);
}*/
/*
int	ft_isupper(int c)
{
	return (c <= 'Z' && c >= 'A');
}

int	ft_islower(int c)
{
	return (c <= 'z' && c >= 'a');
}

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}
#include<stdio.h>

int	main(int a, char **c)
{
	(void)a;
	while (*c[1])
	printf("%d\n",ft_isalnum(*c[1]++));
}*/
/*
#include<stdio.h>

int	main(int a, char **c)
{
	(void)a;
	while (*c[1])
	printf("%d\n",ft_isdigit(*c[1]++));
}*/

/*
int     main(int ac, char **av)
{
        if (ac == 3)
        {
                printf("%d\n", ft_memcmp(av[0], av[2], atoi(av[3])));
                printf("%d\n", memcmp(av[0], av[2], atoi(av[3])));
        }
}
*/

/*
int	main(int a, char **c)
{
	char *r;
	r = ft_strchr("teste", 0);
	printf("%s\n", r);
}*/



/*size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lensrc;

	i = 0;
	lensrc = 0;
	while (src[lensrc])
		lensrc++;
	if (size == 0)
		return (lensrc);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lensrc);
}*/
STRTRIM

/*
int	main(void)
{
	char	*s;

	s = ft_strtrim("ab cd  f    ", " ");
	printf("ft_strtrim(|ab cd  f    |, "" ) = |%s|", s);
	free(s);
}
*/
