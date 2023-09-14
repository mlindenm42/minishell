/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/13 01:03:40 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->tkn, tkn->val);
//printf("nd token%i, %s\n", tkn->tkn, tkn->val);
//printf("%i\n", pipes);

//writing io_part to a row
static void	iototbl(t_tkn *tkn, t_cmdtable *row)
{
	if ((tkn - 1)->tkn == LT || (tkn - 1)->tkn == LLT)
	{
		row->curr_i->pth = tkn->val;
		row->curr_i->io = (tkn - 1)->tkn;
		(row->curr_i)++;
	}
	else
	{
		row->curr_o->pth = tkn->val;
		row->curr_o->io = (tkn - 1)->tkn;
		(row->curr_o)++;
	}
}

//writing args to a row
static void	argtotbl(t_tkn *tkn, t_cmdtable *row)
{
	*row->curr_a = tkn->val;
	(row->curr_a)++;
}

//writing args to a row
static void	cmdtotbl(t_tkn *tkn, t_cmdtable *row, char *envp[])
{
	row->cmd = getpath(tkn->val, envp);
	*row->args = tkn->val;
	(row->curr_a)++;
}

//fills a row of the table (one pipe)
//returns either the token that should go to the next row
//or the last token in the token array
t_tkn	*to_row(t_tkn *tkn, t_cmdtable *row, int npipes, char *envp[])
{
	t_tkn	*tkn0;

	tkn0 = tkn;
	if (row->pipeid < npipes - 1)
		(row + 1)->pipeid = row->pipeid + 1;
	while (tkn->tkn != PIPE && tkn->tkn != END)
	{
		if (tkn->tkn == WORD)
		{
			if (tkn == tkn0 || ((tkn - 2)->tkn >= GT && (tkn - 2)->tkn <= LLT))
				cmdtotbl(tkn, row, envp);
			else if ((tkn - 1)->tkn != WORD)
				iototbl(tkn, row);
			else
				argtotbl(tkn, row);
		}
		tkn++;
	}
	row->args[row->nargs] = NULL;
	if (tkn->tkn != END)
		return (tkn + 1);
	return (tkn);
}

//takes an array of tokens and outputs the command table
t_cmdtable	*parser(t_tkn *tkns, char *envp[], t_errdata *err)
{
	t_cmdtable	*tbl;
	t_cmdtable	*row;
	int			pipes;
	t_tkn		*tkn;

	tkn = tkns;
	pipes = calcpipes(tkns);
	tbl = malloc(pipes * sizeof(t_cmdtable));
	row = tbl;
	if (tbl == NULL)
		errfree(err, NULL, NULL, STP);
	else
		tbl->pipeid = 0;
	while (tkn->tkn != END && err->stop == CNT)
	{
		rowalloc(row, tkn, pipes, err);
		if (err->stop == CNT)
			tkn = to_row(tkn, row, pipes, envp);
		row++;
	}
	return (tbl);
}
