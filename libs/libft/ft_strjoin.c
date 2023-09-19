/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:35:31 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/07 00:11:56 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if ((s1 != 0) && (s2 != 0))
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = malloc(len1 + len2 + 1);
		if (str != 0)
		{
			ft_strlcpy(str, s1, len1 + 1);
			ft_strlcat(str, s2, len2 + len1 + 1);
		}
		return (str);
	}
	else
		return (0);
}
