/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 10:23:51 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
static void	cmdtotbl(t_tkn *tkn, t_cmdtable *row, char *envp[], t_errdata *err)
{
	row->cmd = getpath(tkn->val, envp, err);
	*row->args = tkn->val;
	if (row->cmd != tkn->val)
		row->path_flag = 1;
	(row->curr_a)++;
}

//fills a row of the table (one pipe)
//returns either the token that should go to the next row
//or the last token in the token array
static t_tkn	*to_row(t_tkn *t, t_cmdtable *row, int npipes, t_errdata *err)
{
	t_tkn	*t_copy;

	while (t->type == WORD && !valid(t->val, err->envp))
		t++;
	t_copy = t;
	if (row->pipeid < npipes - 1)
		(row + 1)->pipeid = row->pipeid + 1;
	while (t->type != PIPE && t->type != END)
	{
		if (t->type == WORD)
		{
			if ((t == t_copy || (t - 2 >= t_copy && (t - 2)->type >= GT
						&& (t - 2)->type <= LLT)) && valid(t->val, err->envp))
				cmdtotbl(t, row, err->envp, err);
			else if ((t - 1)->type >= GT && (t - 1)->type <= LLT)
				iototbl(t, row);
			else if (valid(t->val, err->envp))
				argtotbl(t, row);
		}
		t++;
	}
	row->args[row->nargs] = NULL;
	if (t->type != END)
		return (t + 1);
	return (t);
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
	err->tbl = create_elem(&err->gc, sizeof(t_cmdtable), pipes);
	err->tbl->eflag = 0;
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
