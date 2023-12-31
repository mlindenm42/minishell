/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:17:37 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/26 18:17:37 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n))
	{
		if ((s1[i] == '\0') || (s2[i] == '\0') || s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		else
			i++;
	}
	return (0);
}
