/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:32:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/14 01:25:08 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h> // printf();

static int	check_string(char *str)
{
	int	i;

	i = 0;
	if (*(str) == '+' || *(str) == '-')
		i++;
	if (*(str + i) < '0' || *(str + i) > '9')
		return (0);
	while (*(str + i) != '\0')
	{
		if (*(str + i) >= '0' && *(str + i) <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	split_input(char *input)
{
	int		j;

	j = 0;
	get_data()->tokens = NULL;
	get_data()->tokens = ft_split(input, ' ');
	if (get_data()->tokens == NULL)
		error("split failed!\n");
	while (*(get_data()->tokens + j) != NULL)
	{
		if (!check_string(*(get_data()->tokens + j)))
			error("invalid characters as arguments!\n");
		j++;
	}
	j = 0;
	// free_ptrptr(p);
}

void	lexer(char *input)
{
	int		i;

	get_data()->tokens = ft_split(input, ' ');
	i = 0;
	while (get_data()->tokens[i] != NULL)
		printf("%d\n", ++i);
	// split_input(input);
	printf("%s \n", get_data()->tokens[0]);
	i = 0;
	while (get_data()->tokens[i] != NULL)
	{
		if (get_data()->tokens[i] != NULL)
			free(get_data()->tokens[i++]);
	}
	if (get_data()->tokens != NULL)
		free(get_data()->tokens);
}
