/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/19 20:27:26 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->token, tkn->val);
//printf("nd token%i, %s\n", tkn->token, tkn->val);
//printf("%i\n", pipe_cnt);

//dummy function lexer simulator
//simulates: cat -e f1 | grep line > out1 > out2
t_token *lexer()
{
	t_token *tkns;
	int size;

	size = 11;
	tkns = malloc(size * sizeof(t_token));
	tkns[0].token = WORD;
	tkns[0].val = "cat";
	tkns[1].token = WORD;
	tkns[1].val = "-e";
	tkns[2].token = WORD;
	tkns[2].val = "f1";
	/* tkns[3].token = PIPE;
	tkns[4].token = WORD;
	tkns[4].val = "grep";
	tkns[5].token = WORD;
	tkns[5].val = "lin";
	tkns[6].token = GT;
	tkns[7].token = WORD;
	tkns[7].val = "out1";*/
	tkns[3].token = GT;
	tkns[4].token = WORD;
	tkns[4].val = "out1";
	tkns[5].token = END;
	tkns[5].val = NULL;
	return (tkns);
}

//writing io_part to a row
void	iototbl(t_token *tkn, t_cmdtable *row)
{
	if ((tkn - 1)->token == LT || (tkn - 1)->token == LLT)
	{
		row->curr_i->file = tkn->val;
		row->curr_i->io = (tkn - 1)->token;
		(row->curr_i)++;
	}
	else
	{
		row->curr_o->file = tkn->val;
		row->curr_o->io = (tkn - 1)->token;
		(row->curr_o)++;
	}
}

//writing args to a row
void	argtotbl(t_token *tkn, t_cmdtable *row)
{
	*row->curr_a = tkn->val;
	(row->curr_a)++;
}

//fills a row of the table (one pipe)
//returns either the token that should go to the next row
//or the last token in the token array
t_token	*to_row(t_token *tkn, t_cmdtable *row, int npipes, char *envp[])
{
	t_token *starttkn;

	starttkn = tkn;
	if (row->pipe < npipes - 1)
		(row + 1)->pipe = row->pipe + 1;
	while (tkn->token != PIPE && tkn->token != END)
	{
		if (tkn->token == WORD)
		{
			if (tkn == starttkn)
			{
				row->cmd = getpath(tkn->val, envp);
				*row->args = tkn->val;
				(row->curr_a)++;
			}
			else if((tkn - 1)->token != WORD)
				iototbl(tkn, row);
			else
				argtotbl(tkn, row);
		}
		tkn++;
	}
	row->args[row->nargs] = NULL;
	if (tkn->token != END)
		return (tkn + 1);
	else
		return (tkn);
}

//takes an array of tokens and outputs the command table
t_cmdtable	*parser (t_token *tkns, char *envp[])
{
	t_cmdtable	*tbl;
	t_cmdtable	*row;
	int			pipe_cnt;
	t_token		*tkn;

	tkn = tkns;
	pipe_cnt = calcpipes(tkns);
	tbl = malloc(pipe_cnt * sizeof(t_cmdtable));
	row = tbl;
	if (tbl == NULL)
		err_handler(tbl);
	if (tbl != NULL)
		tbl->pipe = 0;
	while (row != NULL && tkn->token != END)
	{
		rowalloc(row, tkn, pipe_cnt);
		tkn = to_row(tkn, row, pipe_cnt, envp);
		row++;
	}
	return (tbl);
}
