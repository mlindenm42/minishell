/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:13:58 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/07 14:55:28 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if ((lst != 0) && (f != 0))
	{
		while (lst != 0)
		{
			if (lst->content != 0)
				f(lst->content);
			lst = lst->next;
		}
	}
}
