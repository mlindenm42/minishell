/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/11 20:28:49 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(char *input, char *envp[], t_errdata *err)
{
	t_cmdtable	*tbl;

	lexer(input);
	if (get_data()->tokens->type != END)
	{
		tbl = parser(get_data()->tokens, envp, err);
		dprintf(2, "tbl %p\n", tbl);
		//print_table(tbl, tbl->nrows);
		expander(tbl, err, envp);
		//print_table(tbl, tbl->nrows);
		// dprintf(2, "pipe0 %i\n", tbl->pipeid);
		// dprintf(2, "pipe1 %i\n", (tbl + 1)->pipeid);
		// dprintf(2, "pipe2 %i\n", (tbl + 2)->pipeid);
		if (err->stop == CNT)
			executor(tbl, envp, err);
	}
	//dprintf(2, "pipe2 %i\n", (tbl[tbl->nrows - 2]).pipeid);
	free_rows(&tbl[tbl->nrows - 1]);
	free(tbl);
}