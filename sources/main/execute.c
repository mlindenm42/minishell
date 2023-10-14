/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/13 20:20:16 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(char *input, char *envp[], t_errdata *err)
{
	t_cmdtable	*tbl;
	char *test;

	tbl = NULL;
	lexer(input);
	if (get_data()->tokens->type != END)
	{
		tbl = parser(get_data()->tokens, envp, err);
		//print_table(tbl, tbl->nrows);
		expander(tbl, err, envp);
		//print_table(tbl, tbl->nrows);
		// dprintf(2, "pipe0 %i\n", tbl->pipeid);
		// dprintf(2, "pipe1 %i\n", (tbl + 1)->pipeid);
		// dprintf(2, "pipe2 %i\n", (tbl + 2)->pipeid);
		if (err->stop == CNT)
			executor(tbl, envp, err);
		//printf("p: %p,\n", tbl);
	}
	if (tbl != NULL)
	{
		free_tbl(&tbl);
		//dprintf(2, "in f %p\n", tbl->infiles);
		//free_rows(&tbl[tbl->nrows - 1]);
		//free(tbl);
	}
	err->tbl = NULL;
}