/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/23 22:26:56 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void errinit(t_errdata *err)
{
	err->name = "minishell";
	err->type = NOERR;
	err->stat = 0;
	err->stop = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	//char	*input;
	t_tkn *tkns;
	t_cmdtable *tbl;
	t_errdata err;

	envp = NULL;
	errinit(&err);
	tkns = lexer();
	tbl = parser(tkns, envp, &err);
	print_table(tbl, tbl->nrows);
	executor(tbl, envp, &err);

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
