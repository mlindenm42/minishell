/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 21:20:55 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//frees every string in an array of strings and then the array itself
void	free_arr(char **arr)
{
	char	**str;

	if (arr != NULL)
	{
		str = arr;
		while (*str != NULL)
		{
			free(*str);
			*str = NULL;
			str++;
		}
		free(arr);
	}
}

//copies strings from one array to another
//returns a pointer to the new array
char	**copy_arr(char **newarr, char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		newarr[i] = arr[i];
		i++;
	}
	newarr[i] = NULL;
	return (newarr);
}

//frees a string
void	free_str(char **s)
{
	//if (*s != NULL)
	//{
	//	//dprintf(2, "s %p\n", s);
	//	free(*s);
	//	*s = NULL;
	//	//dprintf(2, "s %p\n", s);
	//}
}

//returns length of a null ending array of srings including null
int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i + 1);
}
