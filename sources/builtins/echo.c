/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/15 16:10:00 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char *argv[])
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	while (argv[i] != NULL)
	{
		if (i == 1 && ft_strncmp(argv[i], "-n", 2) == 0)
			newline = FALSE;
		else if (argv[i + 1] != NULL)
			printf("%s ", argv[i]);
		else if (newline == TRUE)
			printf("%s\n", argv[i]);
		else
			printf("%s", argv[i]);
		i++;
	}
}

//char *getenv(const char *name)

/* void	echo(char *argv[])
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	while (argv[i] != NULL)
	{
		if (i == 1 && ft_strncmp(argv[i], "-n", 2) == 0)
			newline = FALSE;
		else
			printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(1, ' ');
	}
	if (newline == TRUE)
		ft_putchar_fd(1, '\n');
} */
