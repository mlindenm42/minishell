/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/18 23:36:28 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//tester functions
//to be removed in final version

void	printargs(char **args, int size)
{
	int	i;

	i = 0;
	while (i <= size - 1)
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("\n");
}

void	printio(t_iof *files, int n)
{
	int	i;

	i = 0;
	while (i <= n - 1)
	{
		printf("%i, %s ", files[i].io, files[i].file);
		i++;
	}
	printf("\n");
}

void	print_table(t_cmdtable *tbl, int size)
{
	int	i;

	i = 0;
	while (i <= size - 1)
	{
		printf("pipe%i: %s | ", tbl[i].pipe, tbl[i].cmd);
		printf("args: ");
		printargs(tbl[i].args, tbl[i].nargs + 1);
		printf("\n in: ");
		printio(tbl[i].infiles, tbl[i].nins);
		printf("\n out: ");
		printio(tbl[i].outfiles, tbl[i].nouts);
		i++;
	}
	printf("\n");
}
