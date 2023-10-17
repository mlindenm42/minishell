/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:17:45 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 10:30:41 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	gotit(t_free_elem **elem1, t_free_elem *elem2)
{
	elem2->next = *elem1;
	*elem1 = elem2;
}

static t_free_elem	*new_free_elem(t_free *ree, void *elem)
{
	t_free_elem	*free_elem;

	free_elem = NULL;
	ree->elemcounter = 1;
	free_elem = malloc(sizeof(t_free_elem));
	if (free_elem == NULL)
		return (NULL);
	free_elem->elem = elem;
	free_elem->free_func = &free;
	free_elem->next = NULL;
	return (free_elem);
}

void	*create_elem(t_free *ree, int i, int j)
{
	void	*elem;

	elem = NULL;
	elem = ft_calloc(j, i);
	if (elem == NULL)
		return (NULL);
	gotit(&ree->elem, new_free_elem(ree, elem));
	return (elem);
}

void	free_data(t_free *ree, t_free_elem *elem)
{
	t_free_elem	*tmp;

	if (ree->elemcounter == 0)
		return ;
	while (elem != NULL)
	{
		tmp = elem;
		elem = elem->next;
		if (tmp->elem != NULL)
			tmp->free_func(tmp->elem);
		free(tmp);
	}
	ree->elemcounter = 0;
}
