/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:43:21 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/12 22:57:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*start;
	size_t		needle_len;
	const char	*end_pointer;

	if (ft_strncmp("", needle, 1) == 0)
		return ((char *) haystack);
	needle_len = ft_strlen(needle);
	if ((haystack == 0) && (len == 0))
		return (0);
	else
	{
		if (len > ft_strlen(haystack))
			len = ft_strlen(haystack);
		end_pointer = &haystack[len - 1];
		start = ft_strchr(haystack, *needle);
		while ((start != 0) && (end_pointer + 1 >= needle_len + start))
		{
			if ((ft_strncmp(start, needle, needle_len) == 0))
				return ((char *) start);
			haystack++;
			start = ft_strchr(haystack, *needle);
		}
		return (0);
	}
}
