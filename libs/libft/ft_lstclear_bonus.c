/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:13:58 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/07 15:03:26 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstpenultimate(t_list *lst)
{
	if ((lst != 0) && (lst->next != 0))
	{
		while (lst->next->next != 0)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*penultimate;

	if ((lst != 0) && (del != 0))
	{
		penultimate = ft_lstpenultimate(*lst);
		while ((penultimate != 0) && (penultimate->next != 0))
		{
			ft_lstdelone(penultimate->next, del);
			penultimate->next = 0;
			penultimate = ft_lstpenultimate(*lst);
		}
		ft_lstdelone(penultimate, del);
		*lst = 0;
	}
}
