/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:20:56 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:20:56 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	length;

	length = ft_strlen(s1);
	s2 = (char *)malloc(length + 1);
	if (s2 != 0)
		ft_strlcpy(s2, s1, length + 1);
	return (s2);
}
