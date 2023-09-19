/* ************************************************************************** */
/*   #include "libft.h"                                                       */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:20:20 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:20:20 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
writes len bytes of value c
*/
void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	size_t	count;

	str = b;
	count = 0;
	while (count < len)
	{
		*str = c;
		str++;
		count++;
	}
	return (b);
}
