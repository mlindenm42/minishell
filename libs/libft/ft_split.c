/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:36:03 by mrubina           #+#    #+#             */
/*   Updated: 2023/05/02 14:37:13 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;

	if ((s == 0) || (*s == '\0'))
		return (0);
	else
	{
		count = 0;
		while ((*s == c) && (*s != '\0'))
			s++;
		while ((*s != '\0'))
		{
			while ((*s != c) && (*s != '\0'))
				s++;
			while ((*s == c) && (*s != '\0'))
				s++;
			count ++;
		}
		return (count);
	}
}

static char	*new_word(const char *start, size_t len0, char **arr, int i)
{
	char	*new;

	new = (char *)malloc(len0);
	if (new != 0)
		ft_strlcpy(new, start, len0);
	else
	{
		while (i > 0)
		{
			i--;
			free(arr[i]);
			arr[i] = 0;
		}
	}
	return (new);
}

size_t	find_len0(const char **current, const char *word_start)
{
	size_t	len0;

	if ((*current != 0) && (**current != '\0'))
	{
		(*current)++;
		len0 = *current - word_start;
	}
	else
		len0 = ft_strlen(word_start) + 1;
	return (len0);
}

static int	wordiszero(char *word, int *index, char ***arr)
{
	if (word != 0)
	{
		(*index)++;
		return (0);
	}
	else
	{
		free(*arr);
		*arr = 0;
		return (1);
	}	
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	const char	*word_start;
	size_t		len0;
	int			i;

	i = 0;
	arr = (char **) malloc ((word_count(s, c) + 1) * 8);
	while ((s != 0) && (*s != '\0') && (arr != 0))
	{
		word_start = s;
		s = ft_strchr(s, c);
		len0 = find_len0(&s, word_start);
		if (len0 != 1)
		{
			arr[i] = new_word(word_start, len0, arr, i);
			if (wordiszero(arr[i], &i, &arr))
				return (0);
		}
		while ((s != 0) && (*s == c) && (*s != '\0'))
			s++;
	}
	if (arr != 0)
		arr[i] = 0;
	return (arr);
}
