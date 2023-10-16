/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 15:13:06 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
.. level up
../ level up and start from it
. cur dir
./
/ -abs path

 */
int	cd(char *argv[])
{
	// int	i;
	char *curdir;
	char *newdir;
	char *upperdir;

	curdir = getcwd(NULL, 0);
	// if (argv[1] != NULL && argv[1][0] == '/')
	// 	newdir = argv[1];
	// else if (argv[1] != NULL && argv[1][0] == '.' && argv[1][1] == '.')
	// {
	// 	upperdir = ft_substr(curdir, 0, ft_strrchr(curdir, '/') - curdir);
	// 	newdir = ft_strjoin(upperdir, &argv[1][2]);
	// 	free_str(&upperdir);
	// }
	// else if (argv[1] != NULL && argv[1][0] == '.' && argv[1][1] != '.')
	// 	newdir = ft_strjoin(curdir, &argv[1][1]);
	// else if (argv[1] != NULL && ft_strchr(argv[1], '/') == NULL)
	// {
	// 	upperdir = ft_strjoin("/", argv[1]);
	// 	newdir = ft_strjoin(curdir, upperdir);
	// 	free(upperdir);
	// }
	if (chdir(argv[1]) == -1)
		return (1);
	// if (argv[1] != NULL && argv[1][0] != '/')
		// free_str(&newdir);
	return (0);
}

void	pwd(void)
{
	char *curdir;

	curdir = getcwd(NULL, 0);
	if (curdir != NULL)
	{
		printf("%s\n", curdir);
		free(curdir);
	}
}

void	exitbuiltin(char *argv[], t_errdata *err)
{
	int	stat;
	char *tmp;

	stat = 0;
	if (argv[1] != NULL && argv[2] == NULL)
	{
		stat = ft_atoi(argv[1]);
		if (stat == 0)
		{
			tmp = ft_strjoin(argv[1], ": numeric argument required");
			custom_err("bash: exit", tmp);
			stat = 255;
			free(tmp);
		}
	}
	// freeall(err);
	printf("exit\n");
	exit(stat);
}
