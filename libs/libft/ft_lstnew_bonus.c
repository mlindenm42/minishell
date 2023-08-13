/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:06:04 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/07 15:02:11 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*mylist;

	mylist = (t_list *)malloc(16);
	if (mylist != 0)
	{
		mylist->content = content;
		mylist->next = 0;
	}
	return (mylist);
}
