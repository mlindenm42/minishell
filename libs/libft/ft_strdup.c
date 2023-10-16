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
#include "../../sources/trash/trash.h"
#include "../../includes/structs.h"

char	*ft_strdup(const char *s1, t_errdata *err)
{
	char	*s2;
	size_t	length;

	length = ft_strlen(s1);
	s2 = create_pile(&err->gc, sizeof(char), length + 1);
	if (s2 != 0)
		ft_strlcpy(s2, s1, length + 1);
	return (s2);
}
