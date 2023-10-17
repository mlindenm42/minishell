/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:18:50 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 22:18:50 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/minishell.h"

char	*ft_strdup(const char *s1, t_errdata *err)
{
	char	*s2;
	size_t	length;

	length = ft_strlen(s1);
	s2 = create_elem(&err->gc, sizeof(char), length + 1);
	if (s2 != 0)
		ft_strlcpy(s2, s1, length + 1);
	return (s2);
}
