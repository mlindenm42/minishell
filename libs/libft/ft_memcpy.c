/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:19:58 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:19:58 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*temp_dst;
	const char	*temp_src;

	i = 0;
	temp_dst = dst;
	temp_src = src;
	while ((i < n) && ((temp_dst != 0) || (temp_src != 0)))
	{
		temp_dst[i] = temp_src[i];
		i++;
	}
	return (dst);
}
