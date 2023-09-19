/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:21:09 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:21:09 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	len_src = ft_strlen(src);
	if (dst != 0)
		len_dst = ft_strlen(dst);
	else
		len_dst = 0;
	i = len_dst;
	while ((i + 1 < dstsize) && (src[i - len_dst] != '\0'))
	{
		dst[i] = src[i - len_dst];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	if (dstsize < len_dst)
		return (len_src + dstsize);
	else
		return (len_src + len_dst);
}
