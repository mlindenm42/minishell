/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:35:31 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 22:19:17 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../sources/trash/trash.h"
#include "../../includes/structs.h"

char	*ft_strjoin(char const *s1, char const *s2, t_errdata *err)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if ((s1 != 0) && (s2 != 0))
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = create_pile(&err->gc, sizeof(char), len1 + len2 + 1);
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
