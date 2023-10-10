/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/09 01:28:28 by mrubina          ###   ########.fr       */
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
		//print_table(tbl, tbl->nrows);
		expander(tbl, err, envp);
		//print_table(tbl, tbl->nrows);
		if (err->stop == CNT)
			executor(tbl, envp, err);
	}
}