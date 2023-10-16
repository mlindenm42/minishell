

#include "../../sources/trash/trash.h"
#include "libft.h"

#include <stdlib.h> // free

//Global//

void	*create_pile(t_gc *gc, int size, int quantity)
{
	void	*pile;

	pile = NULL;
	pile = ft_calloc(quantity, size);
	if (pile == NULL)
		return (NULL);
	pile_up(&gc->dump, new_container(gc, pile));
	return (pile);
}

t_dump	*new_container(t_gc *gc, void *pile)
{
	t_dump	*container;

	container = NULL;
	gc->dump_status = 1;
	container = malloc(sizeof(t_dump));
	if (container == NULL)
		return (NULL);
	container->garbage_pile = pile;
	container->free_func = &free;
	container->next = NULL;
	return (container);
}

void	pile_up(t_dump **dump, t_dump *pile)
{
	pile->next = *dump;
	*dump = pile;
}

void	burn_it_down(t_gc *gc, t_dump *dump)
{
	t_dump	*tmp;

	if (gc->dump_status == 0)
		return ;
	while (dump != NULL)
	{
		tmp = dump;
		dump = dump->next;
		if (tmp->garbage_pile != NULL)
			tmp->free_func(tmp->garbage_pile);
		free(tmp);
	}
	gc->dump_status = 0;
}

void	free_double(void **double_pointer)
{
	int	i;

	i = -1;
	while (double_pointer[++i] != NULL)
		free(double_pointer[i]);
	free(double_pointer[i]);
	free(double_pointer);
}
