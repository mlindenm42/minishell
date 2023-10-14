/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/14 06:52:25 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char *argv[])
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
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

/* void	pwd(void)
{

} */

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
