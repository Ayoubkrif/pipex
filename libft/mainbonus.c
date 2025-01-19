#include "libft.h"
int     main(int a, char **c)
{
        t_list  a;
        t_list  b;
        t_list  c;

        a = ft_lstnew((void *)c[1]);
        b = ft_lstnew((void *)c[2]);
        c = ft_lstnew((void *)c[3]);
        ft_lstadd_back(&a, b);
        ft_lstadd_back(&a, c);
        ft_putnbr_fd(ft_lstsize(a));
        ft_lstdelone(c);
        b->next = NULL;
        ft_putnbr_fd(ft_lstsize(a));
        ft_lstmap();
}

