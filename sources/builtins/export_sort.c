/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/27 20:01:13 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//helper function for sorting
//returns 1 if the first string is smaller
int	issmaller(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len2 > len1)
		len1 = len2;
	return (ft_strncmp(str1, str2, len1) < 0);
}

//helper function for sorting
//replaces an element of the array with the smallest
void	replace(char **arr, int ind, int n)
{
	int		i;
	char	*tmp;

	i = ind + 1;
	while (i <= n - 1)
	{
		if (issmaller(arr[i], arr[ind]))
		{
			tmp = arr[ind];
			arr[ind] = arr[i];
			arr[i] = tmp;
		}
		i++;
	}
}

//sorts an array of strings in ascending order (A -> z)
void	arr_sort(char **arr, int n)
{
	int	i;

	i = 0;
	while (i <= n - 1)
	{
		replace(arr, i, n);
		i++;
	}
}
