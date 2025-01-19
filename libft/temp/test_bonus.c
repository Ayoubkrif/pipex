#include "libft.h"
#include <stdio.h>
void	del(void *content)
{
	printf("del content:%s\n",(char *)content);
}
void	iter(void *content)
{
	printf("iter content :%s\n",(char *)content);
}

void	*capitaliser(void *content)
{
	int	i = 0;

	ft_putstr_fd("chaine a capitaliser:", 1);
	ft_putstr_fd((char *)content, 1);
	ft_putstr_fd("\n", 1);
	while (((unsigned char *)content)[i])
	{
		((char *)content)[i] = ft_toupper(((char *)content)[i]);
		i++;
	}
	return (content);
}

void	printlist(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)(lst->content));
		lst = lst->next;
	}
}

int	main(int a, char **c)
{
	t_list	*head = ft_lstnew((void *)c[1]);
	printlist(head);
	int	i = 2;
	while (i < a)
	{
		ft_lstadd_back(&head, ft_lstnew((void *)c[i]));
		i++;
	}
	printf("+++\n");
	printlist(head);
	printf("+++\n");
	t_list	*test = ft_lstnew((void *)"blabla");
	ft_lstadd_back(&head, test);
	printlist(head);
	printf("lstsize : %d\n",ft_lstsize(head));
	printf("print list last de head:\n");
	printlist(ft_lstlast(head));
	ft_lstclear(&test, del);
	printf("print list head sans blabla:\n");
	printlist(head);
	printf("avant lstmap\n");
	test = ft_lstmap(head, capitaliser, del);
	ft_lstclear(&head, del);
	ft_lstclear(&test, del);
}
