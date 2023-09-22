/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/23 00:09:14 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// dprintf(2, "p %p\n", str);
// dprintf(2, "t %s\n", str);


void errinit(t_errdata *err, char *envp[])
{
	err->stat = 0;
	err->statstr = NULL;
	err->stop = CNT;
	set_loc_env(envp, err);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_tkn	*tkns;
	t_cmdtable	*tbl;
	t_errdata	err;

	errinit(&err, envp);
	tkns = lexer();
	tbl = parser(tkns, err.envp_loc, &err);
	expander(tbl, &err);
	print_table(tbl, tbl->nrows);
	if (err.stop == CNT)
		executor(tbl, err.envp_loc, &err);
	printf("\nexit stat: %i\n", err.stat);
	//printenv(err.envp_loc);
	return (0);
}
