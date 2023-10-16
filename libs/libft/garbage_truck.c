/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_truck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:20:10 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 22:20:15 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sources/trash/trash.h"
#include "libft.h"

#include <stdlib.h> // free

//Local//

void	*collect_trash(t_gc *gc, int size, int quantity)
{
	void	*trash;

	trash = ft_calloc(quantity, size);
	if (trash == NULL)
		return (NULL);
	throw_garbage_on_top(&gc->bin, new_garbage_bag(gc, trash));
	return (trash);
}

t_bin	*new_garbage_bag(t_gc *gc, void *trash)
{
	t_bin	*garbage_bag;

	gc->bin_status = 1;
	garbage_bag = malloc(sizeof(t_bin));
	if (garbage_bag == NULL)
		return (NULL);
	garbage_bag->garbage = trash;
	garbage_bag->free_func = &free;
	garbage_bag->next = NULL;
	return (garbage_bag);
}

void	throw_garbage_on_top(t_bin **garbage_pile, t_bin *garbage)
{
	garbage->next = *garbage_pile;
	*garbage_pile = garbage;
}

void	empty_trash(t_gc *gc, t_bin	*bin)
{
	t_bin	*tmp;

	if (gc->bin_status == 0)
		return ;
	while (bin != NULL)
	{
		tmp = bin;
		bin = bin->next;
		if (tmp->garbage != NULL)
			tmp->free_func(tmp->garbage);
		free(tmp);
	}
	gc->bin_status = 0;
}

//void	nuke_trash(t_cub3d	*cube)
//{
//	empty_trash(&cube->gc, cube->gc.bin);
//	burn_it_down(&cube->gc, cube->gc.dump);
//}
