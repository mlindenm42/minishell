/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/15 12:25:21 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
.. level up
../ level up and start from it
~/ cur user
. cur dir
./
/ -abs path

 */
int	cd(char *argv[], t_errdata *err)
{
	// int	i;
	char *curdir;
	char *newdir;
	char *upperdir;

	curdir = getcwd(NULL, 0);
//dprintf(2, "my id%s\n", curdir );
	if (argv[1] != NULL && argv[1][0] == '/')
		newdir = argv[1];
	else if (argv[1] != NULL && argv[1][0] == '.' && argv[1][1] == '.')
	{
		upperdir = ft_substr(curdir, 0, ft_strrchr(curdir, '/') - curdir);
		newdir = ft_strjoin(upperdir, &argv[1][2]);
		free_str(&upperdir);
	}
	else if (argv[1] != NULL && argv[1][0] == '.' && argv[1][1] != '.')
		newdir = ft_strjoin(curdir, &argv[1][1]);
	else if (ft_strchr(argv[1], '/') == NULL)
	{
		upperdir = ft_strjoin("/", argv[1]);
		newdir = ft_strjoin(curdir, upperdir);
		free(upperdir);
	}
	dprintf(2, "%s\n", newdir);
	if (chdir(newdir) == -1)
		return (1);
	if (argv[1] != NULL && argv[1][0] != '/')
		free_str(&newdir);

	//change PWD and OLDPW
	//./.. doesn't work correctly
	return (0);
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
