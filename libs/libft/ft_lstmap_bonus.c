/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:13:58 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/16 18:02:25 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create(void *content, void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;
	t_list	*new_node;

	new_content = f(content);
	new_node = ft_lstnew(new_content);
	if (new_node == 0)
		del(new_content);
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*new_node;
	t_list	*previous_node;

	previous_node = 0;
	start = 0;
	while ((lst != 0) && (f != 0) && (del != 0))
	{
		new_node = create(lst->content, f, del);
		if (new_node == 0)
		{
			ft_lstclear(&previous_node, del);
			return (0);
		}
		if (previous_node != 0)
			ft_lstadd_back(&previous_node, new_node);
		previous_node = new_node;
		if (start == 0)
			start = new_node;
		lst = lst->next;
	}
	return (start);
}
