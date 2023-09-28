/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/28 17:09:19 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void errinit(t_errdata *err)
{
	err->stat = 0;
	err->stop = CNT;
	err->statstr = NULL;
}

void	execute(char *input, char *envp[])
{
	t_cmdtable	*tbl;
	t_errdata	err;

	errinit(&err);
	lexer(input);
	if (get_data()->tokens->type != END)
	{
		tbl = parser(get_data()->tokens, envp, &err);
		expander(tbl, &err);
		//print_table(tbl, tbl->nrows);
		if (err.stop == CNT)
			executor(tbl, envp, &err);
	}
}