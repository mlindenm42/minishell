/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:18:47 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:18:47 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*p;
	long double	product;

	product = (long double) count * (long double) size;
	if (product >= (long double)((size_t)(-1)))
		p = 0;
	else
		p = malloc (size * count);
	if (p != 0)
		ft_bzero(p, count * size);
	return (p);
}
