/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:27:46 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 21:59:32 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start,
		size_t len, t_errdata *err)
{
	char	*substr;
	size_t	str_len;
	size_t	max_len;

	if (s == 0)
		return (0);
	str_len = ft_strlen(s);
	if (start >= str_len)
		max_len = 0;
	else
		max_len = str_len - start;
	if (len > max_len)
		len = max_len;
	substr = create_elem(&err->gc, sizeof(char), len + 1);
	if ((substr != 0) && (s != 0) && (start <= str_len))
		ft_strlcpy(substr, &s[start], len + 1);
	else if ((substr != 0) && (s != 0) && (start > str_len))
		ft_strlcpy(substr, "", len + 1);
	return (substr);
}
