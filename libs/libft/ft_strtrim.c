/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:34:53 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 22:19:53 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../sources/trash/trash.h"
#include "../../includes/structs.h"

char	*ft_strtrim(char const *s1, char const *set, t_errdata *err)
{
	char const	*start;
	char const	*end;
	char		*str;

	start = s1;
	if ((s1 != 0) && (set != 0))
	{
		end = s1 + ft_strlen(s1) - 1;
		while ((ft_strchr(set, *start) != 0) && (*start != '\0'))
			start++;
		while ((ft_strchr(set, *end) != 0) && (end != s1))
			end--;
		if (start > end)
			str = create_pile(&err->gc, sizeof(char), 1);
		else
			str = create_pile(&err->gc, sizeof(char), end - start + 2);
		if ((start <= end) && (str != 0))
			ft_strlcpy(str, start, end - start + 2);
		else if (str != 0)
			*str = '\0';
	}
	else
		str = 0;
	return (str);
}
