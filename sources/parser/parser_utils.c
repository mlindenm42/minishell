/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 10:23:51 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell.h"

/* calculates number of arguments for a single pipeline
we calculate args + cmd which should be argument zero
it calculates the first word token after the pipe
and any word preceeded by (another) word
*/
static int	calcargs(t_tkn *tkns, char *envp[])
{
	int		cnt;
	t_tkn	*first;

	cnt = 0;
	first = tkns;
	while (tkns->type != END && tkns->type != PIPE)
	{
		if (tkns->type == WORD && tkns == first && valid(tkns->val, envp))
			cnt++;
		if (tkns->type == WORD && tkns != first && (tkns - 1)->type == WORD
			&& valid(tkns->val, envp))
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates input files for a pipe
static int	calcins(t_tkn *tkns)
{
	int	cnt;

	cnt = 0;
	while (tkns->type != END && tkns->type != PIPE)
	{
		if (tkns->type == LT || tkns->type == LLT)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates output files for a pipe
static int	calcouts(t_tkn *tkns)
{
	int	cnt;

	cnt = 0;
	while (tkns->type != END && tkns->type != PIPE)
	{
		if (tkns->type == GT || tkns->type == GGT)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//calculates the total number of pipes
int	calcpipes(t_tkn *tkns)
{
	int	cnt;

	cnt = 1;
	while (tkns->type != END)
	{
		if (tkns->type == PIPE)
			cnt++;
		tkns++;
	}
	return (cnt);
}

//we allocate arg array, ins and outs for a pipe
void	rowalloc(t_cmdtable *tbl, t_tkn *tkns, int pipes, t_errdata *err)
{
	tbl->nrows = pipes;
	tbl->nins = calcins(tkns);
	tbl->nouts = calcouts(tkns);
	tbl->nargs = calcargs(tkns, err->envp);
	tbl->infiles = NULL;
	tbl->outfiles = NULL;
	tbl->path_flag = 0;
	tbl->args = create_elem(&err->gc, sizeof(char *), (tbl->nargs + 1));
	if (tbl->nins != 0)
		tbl->infiles = create_elem(&err->gc, sizeof(t_iof), tbl->nins);
	if (tbl->nouts != 0)
		tbl->outfiles = create_elem(&err->gc, sizeof(t_iof), tbl->nouts);
	if (tbl->args == NULL || (tbl->nins != 0 && tbl->infiles == NULL)
		|| (tbl->nouts != 0 && tbl->outfiles == NULL))
		errfree(err, tbl, NULL, STP);
	tbl->curr_a = tbl->args;
	tbl->curr_i = tbl->infiles;
	tbl->curr_o = tbl->outfiles;
}
