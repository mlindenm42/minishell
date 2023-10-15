/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/15 21:32:05 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->type, tkn->val);
//printf("nd token%i, %s\n", tkn->type, tkn->val);
//printf("%i\n", pipes);

//writing io_part to a row
static void	iototbl(t_tkn *tkn, t_cmdtable *row)
{
	if ((tkn - 1)->type == LT || (tkn - 1)->type == LLT)
	{
		row->curr_i->file = tkn->val;
		row->curr_i->io = (tkn - 1)->type;
		(row->curr_i)++;
	}
	else
	{
		row->curr_o->file = tkn->val;
		row->curr_o->io = (tkn - 1)->type;
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
//path_flag means that cmd should be freed separately from tokens
static void	cmdtotbl(t_tkn *tkn, t_cmdtable *row, char *envp[])
{
	row->cmd = getpath(tkn->val, envp);
	*row->args = tkn->val;
	if (row->cmd != tkn->val)
		row->path_flag = 1;
	(row->curr_a)++;
}

//fills a row of the table (one pipe)
//returns either the token that should go to the next row
//or the last token in the token array
t_tkn	*to_row(t_tkn *tkn, t_cmdtable *row, int npipes,  t_errdata *err)
{
	t_tkn	*tkn0;

	//free(tkn);
	//dprintf(2, " %s\n", tkn->val);
	while (tkn->type == WORD && !varvalid(tkn->val, err->envp))
		tkn++;
	tkn0 = tkn;
	//dprintf(2, "pointer to tkn0 %p\n", tkn0);
	//dprintf(2, "pointer to tkns %p\n", tkn);
	//dprintf(2, "pipeid %i\n", row->pipeid);
	if (row->pipeid < npipes - 1)
		(row + 1)->pipeid = row->pipeid + 1;
	while (tkn->type != PIPE && tkn->type != END)
	{
		if (tkn->type == WORD)
		{
			//dprintf(2, "pointer to tkns %p\n", tkn);
			//dprintf(2, "tt %s\n", tkn0->val);
			if ((tkn == tkn0 || (tkn - 2 >= tkn0 && (tkn - 2)->type >= GT
						&& (tkn - 2)->type <= LLT))
						&& varvalid(tkn->val, err->envp))
					cmdtotbl(tkn, row, err->envp);
			else if ((tkn - 1)->type >= GT && (tkn - 1)->type <= LLT)
				iototbl(tkn, row);
			else if (varvalid(tkn->val, err->envp))
				argtotbl(tkn, row);
		}
		tkn++;
	}
	row->args[row->nargs] = NULL;
	if (tkn->type != END)
		return (tkn + 1);
	return (tkn);
}

//takes an array of tokens and outputs the command table
//in the loop to_row function returns the first token of the next row
t_cmdtable	*parser(t_tkn *tkns, t_errdata *err)
{
	t_cmdtable	*row;
	int			pipes;
	t_tkn		*tkn;

	tkn = tkns;
	pipes = calcpipes(tkns);
	err->tbl = malloc(pipes * sizeof(t_cmdtable));
	row = err->tbl;
	if (err->tbl == NULL)
		errfree(err, NULL, NULL, STP);
	else
		err->tbl->pipeid = 0;
	while (tkn->type != END && err->stop == CNT)
	{
		rowalloc(row, tkn, pipes, err);
		if (err->stop == CNT)
			tkn = to_row(tkn, row, pipes, err);
		row++;
	}
	return (err->tbl);
}
