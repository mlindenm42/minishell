/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:19:47 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:19:47 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
returns the difference between the first different characters,
0 if empty string or n = 0
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*t1;
	const unsigned char	*t2;
	size_t				i;

	t1 = s1;
	t2 = s2;
	i = 0;
	while ((i + 1 < n) && (t1[i] == t2[i]))
		i++;
	if (n != 0)
		return (t1[i] - t2[i]);
	else
		return (0);
}
