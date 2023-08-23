/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/24 00:16:37 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//calculates the total number of pipes
int	calcpipes(t_tkn *tkns)
{
	int	cnt;

	cnt = 1;
	while (tkns->tkn != END)
	{
		if (tkns->tkn == PIPE)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates input files for a pipe
int	calcins(t_tkn *tkns)
{
	int	cnt;

	cnt = 0;
	while (tkns->tkn != END && tkns->tkn != PIPE)
	{
		if (tkns->tkn == LT || tkns->tkn == LLT)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates output files for a pipe
int	calcouts(t_tkn *tkns)
{
	int	cnt;

	cnt = 0;
	while (tkns->tkn != END && tkns->tkn != PIPE)
	{
		if (tkns->tkn == GT || tkns->tkn == GGT)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates arguments for a pipe
//we calculate args + cmd which should be argument zero
int	calcargs(t_tkn *tkns)
{
	int		cnt;
	t_tkn	*first;

	cnt = 0;
	first = tkns;
	while (tkns->tkn != END && tkns->tkn != PIPE)
	{
		if (tkns->tkn == WORD && tkns == first)
			cnt++;
		if (tkns->tkn == WORD && tkns != first && (tkns - 1)->tkn == WORD)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//we allocate arg array, ins and outs for a pipe
void	rowalloc(t_cmdtable *tbl, t_tkn *tkns, int pipes, t_errdata *err)
{
	tbl->err = err;
	tbl->nrows = pipes;
	tbl->nins = calcins(tkns);
	tbl->nouts = calcouts(tkns);
	tbl->nargs = calcargs(tkns);
	tbl->args = malloc((tbl->nargs + 1) * sizeof(char *));
	tbl->infiles = malloc(tbl->nins * sizeof(t_iof));
	tbl->outfiles = malloc(tbl->nouts * sizeof(t_iof));
	if (tbl->args == NULL || tbl->infiles == NULL || tbl->outfiles == NULL)
		err_handler(err, tbl, &free_rows, 1);
	tbl->curr_a = tbl->args;
	tbl->curr_i = tbl->infiles;
	tbl->curr_o = tbl->outfiles;
}
