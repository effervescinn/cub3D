# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*p;

	size = 0;
	p = lst;
	while (p)
	{
		p = p->next;
		size++;
	}
	return (size);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (!lst)
		return ;
	if (!*lst)
	{
		(*lst) = new;
		new->next = NULL;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
	new->next = NULL;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	if (!(newlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((ptr = (void *)malloc(count * size)))
	{
		ft_bzero(ptr, count * size);
		return (ptr);
	}
	return (NULL);
}