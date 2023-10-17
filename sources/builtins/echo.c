/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 07:46:10 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char *argv[])
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argv[i] == NULL)
		printf("\n");
	else
	{
		while (argv[i] != NULL)
		{
			if (i == 1 && ft_strncmp(argv[i], "-n", 2) == 0)
				newline = 0;
			else if (argv[i + 1] != NULL)
				printf("%s ", argv[i]);
			else if (newline == 1)
				printf("%s\n", argv[i]);
			else
				printf("%s", argv[i]);
			i++;
		}
	}
}
