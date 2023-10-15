/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/15 02:16:55 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(char *input, char *envp[], t_errdata *err)
{
	t_cmdtable	*tbl;
	// char *test;

	tbl = NULL;
	lexer(input);
	// dprintf(2, "token val %s\n", tkns->val);
	// free(tkns->val);
	if (get_data()->tokens->type != END)
	{
		tbl = parser(get_data()->tokens, err);
		//print_table(tbl, tbl->nrows);
		expander(tbl, err, envp);
		//print_table(tbl, tbl->nrows);
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
