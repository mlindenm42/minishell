/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:01:22 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/18 00:22:37 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	if (n <= dst_len)
		return (ft_strlen(src) + n);
	i = 0;
	while ((dst_len + i) < (n - 1) && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (ft_strlen(src) + dst_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = NULL;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		*(ptr + i) = s[start + i];
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while ((s[i] != '\0') && (s[i] != (unsigned char)c))
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ptr;

	start = 0;
	end = 0;
	ptr = NULL;
	if (set == NULL && s1 != NULL)
		return ((char *)s1);
	else if (s1 != NULL)
	{
		if (ft_strlen(s1) > 0)
			end = ft_strlen(s1) - 1;
		while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
			start++;
		while (end > start && ft_strchr(set, s1[end]) != NULL)
			end--;
		ptr = ft_substr(s1, start, end - start + 1);
	}
	return (ptr);
}
