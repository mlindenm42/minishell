/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/18 19:25:58 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void errinit(t_errdata *err)
{
	err->stat = 0;
	err->statstr = NULL;
	err->stop = CNT;
}

int	main(int argc, char *argv[], char *envp[])
{
	//char	*input;
	t_tkn *tkns;
	t_cmdtable *tbl;
	t_errdata err;

	errinit(&err);
	tkns = lexer();
	tbl = parser(tkns, envp, &err);
	expander(tbl, &err);
	//printf("%p\n", tbl->infiles);
	print_table(tbl, tbl->nrows);
	if (err.stop == CNT)
		executor(tbl, envp, &err);
	printf("\nexit stat: %i\n", err.stat);
	/* rl_bind_key('\t', rl_complete);
	input = readline("Enter something: ");
	if (input && *input)
	{
		add_history(input);
	}
	printf("You entered: %s\n", input);
	free(input); */
	return (0);
}
