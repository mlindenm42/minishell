/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:32:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/13 22:09:26 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h> // printf();

// void	check_arg(t_stack_ptr *p, int argc, char *argv[])
// {
// 	int		i;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	p->ptrptr = NULL;
// 	while (i < argc)
// 	{
// 		p->ptrptr = ft_split(argv[i++], ' ');
// 		if (p->ptrptr == NULL)
// 			error_data(p, "split failed!\n");
// 		while (*(p->ptrptr + j) != NULL)
// 		{
// 			if (!check_string(*(p->ptrptr + j)))
// 				error_data(p, "invalid characters as arguments!\n");
// 			j++;
// 		}
// 		j = 0;
// 		free_ptrptr(p);
// 	}
// }

void	lexer(char *input)
{
	char	**test;
	int		i;

	test = ft_split(input, ' ');
	printf("%s \n", test[0]);
	i = 0;
	while (test[i] != NULL)
	{
		if (test[i] != NULL)
			free(test[i++]);
	}
	if (test != NULL)
		free(test);
}
