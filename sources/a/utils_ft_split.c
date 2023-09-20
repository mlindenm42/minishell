/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:45:36 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/19 17:36:10 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static size_t	ft_strlcpy(char *dest, const char *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (ft_strlen(src));
// 	while (src[i] != '\0' && i < (n - 1))
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (ft_strlen(src));
// }

// static int	arraycounter(char const *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (*s)
// 	{
// 		while (*s == c && *s)
// 			s++;
// 		if (*s != c && *s)
// 			i++;
// 		while (*s != c && *s)
// 			s++;
// 	}
// 	return (i);
// }

// static int	charcounter(char const *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (*s == c && *s)
// 		s++;
// 	while (*(s + i) != c && *(s + i))
// 		i++;
// 	return (i);
// }

// static int	stringmaker(char **ptrptr, char const *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (*s)
// 	{
// 		*(ptrptr + i) = (char *) malloc((charcounter(s, c) + 1) * sizeof(char));
// 		if (*(ptrptr + i) == NULL)
// 		{
// 			while (--i >= 0)
// 			{
// 				free(*(ptrptr + i));
// 				*(ptrptr + i) = NULL;
// 			}
// 			return (0);
// 		}
// 		while (*s == c && *s)
// 			s++;
// 		ft_strlcpy(*(ptrptr + i), s, charcounter(s, c) + 1);
// 		s += charcounter(s, c);
// 		while (*s == c && *s)
// 			s++;
// 		i++;
// 	}
// 	*(ptrptr + i) = NULL;
// 	return (1);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**ptrptr;

// 	ptrptr = NULL;
// 	if (s == NULL)
// 		return (NULL);
// 	ptrptr = (char **) malloc((arraycounter(s, c) + 1) * sizeof(char *));
// 	if (ptrptr == NULL)
// 		return (NULL);
// 	if (!(arraycounter(s, c)))
// 		*(ptrptr) = NULL;
// 	else if (!(stringmaker(ptrptr, s, c)))
// 	{
// 		free (ptrptr);
// 		ptrptr = NULL;
// 		return (NULL);
// 	}
// 	return (ptrptr);
// }
