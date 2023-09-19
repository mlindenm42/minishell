/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/19 17:23:20 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void errinit(t_errdata *err)
{
	err->stat = 0;
	err->statstr = NULL;
	err->stop = CNT;
}

t_data	*get_data(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

int	main(int argc, char *argv[], char *envp[])
{
	//char	*input;
	t_tkn *tkns;
	t_cmdtable *tbl;
	t_errdata err;

	errinit(&err);
	tkns = *get_data()->tokens;
	tbl = parser(tkns, envp, &err);
	expander(tbl, &err);
	//printf("%p\n", tbl->infiles);
	print_table(tbl, tbl->nrows);
	if (err.stop == CNT)
		executor(tbl, envp, &err);
	printf("\nexit stat: %i\n", err.stat);


	terminal();

	return (0);
}
