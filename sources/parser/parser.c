/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/01 21:01:50 by mrubina          ###   ########.fr       */
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

	while (tkn->type == WORD && !varvalid(tkn->val, envp))
		tkn++;
	tkn0 = tkn;
	if (row->pipeid < npipes - 1)
	{
		(row + 1)->pipeid = row->pipeid + 1;
		(row + 1)->err = row->err;
	}
	while (tkn->type != PIPE && tkn->type != END)
	{
		if (tkn->type == WORD)
		{
			if ((tkn == tkn0 || (tkn - 2 >= tkn0 && (tkn - 2)->type >= GT
						&& (tkn - 2)->type <= LLT)) && varvalid(tkn->val, envp))
					cmdtotbl(tkn, row, envp);
			else if ((tkn - 1)->type >= GT && (tkn - 1)->type <= LLT)
				iototbl(tkn, row);
			else if (varvalid(tkn->val, envp))
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
t_cmdtable	*parser(t_tkn *tkns, char *envp[], t_errdata *err)
{
	t_cmdtable	*tbl;
	t_cmdtable	*row;
	int			pipes;
	t_tkn		*tkn;

		// printf("id %i Token type: %d, Value: %s\n", 0, get_data()->tokens[0]->type, get_data()->tokens[0]->val);
	// printf("id %i Token type: %d, Value: %s\n", 1, get_data()->tokens[1]->type, get_data()->tokens[1]->val);
	// printf("id %i Token type: %d, Value: %s\n", 2, get_data()->tokens[2]->type, get_data()->tokens[2]->val);
	// printf("id %i Token type: %d, Value: %s\n", 0, tkns[0].type, tkns[0].val);
	// printf("id %i Token type: %d, Value: %s\n", 0, tkns[1].type, tkns[1].val);

	//printf("pointer to tkns: %p,\n", *get_data()->tokens);
	//exit(0);
	tkn = tkns;
	pipes = calcpipes(tkns);
	tbl = malloc(pipes * sizeof(t_cmdtable));
	row = tbl;
	if (tbl == NULL)
		errfree(err, NULL, NULL, STP);
	else
		tbl->pipeid = 0;
	while (tkn->type != END && err->stop == CNT)
	{
		tbl->err = err;
		rowalloc(row, tkn, pipes, envp);
		if (err->stop == CNT)
			tkn = to_row(tkn, row, pipes, envp);
		row++;
	}
	return (tbl);
}
