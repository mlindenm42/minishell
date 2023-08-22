/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/22 19:34:11 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//calculates the total number of pipes
int	calcpipes(t_token *tkns)
{
	int	cnt;

	cnt = 1;
	while (tkns->token != END)
	{
		if (tkns->token == PIPE)
			cnt++;
		tkns++;
	}
	return(cnt);
}

//calculates input files for a pipe
int	calcins(t_token *tkns)
{
	int	cnt;

	cnt = 0;
	while (tkns->token != END && tkns->token != PIPE)
	{
		if (tkns->token == LT || tkns->token == LLT)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates output files for a pipe
int	calcouts(t_token *tkns)
{
	int	cnt;

	cnt = 0;
	while (tkns->token != END && tkns->token != PIPE)
	{
		if (tkns->token == GT || tkns->token == GGT)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates arguments for a pipe
//we calculate args + cmd which should be argument zero
int	calcargs(t_token *tkns)
{
	int		cnt;
	t_token	*first;

	cnt = 0;
	first = tkns;
	while (tkns->token != END && tkns->token != PIPE)
	{
		if (tkns->token == WORD && tkns == first)
			cnt++;
		if (tkns->token == WORD && tkns != first && (tkns - 1)->token == WORD)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//we allocate arg array, ins and outs for a pipe
void	rowalloc(t_cmdtable *tbl, t_token *tkns, int pipes, t_errdata *err)
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
		err_handler(err, tbl, &free_rows);
	tbl->curr_a = tbl->args;
	tbl->curr_i = tbl->infiles;
	tbl->curr_o = tbl->outfiles;
}
