/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/14 17:40:51 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell.h"

//calculates the total number of pipes
int	calcpipes(t_tkn *tkns)
{
	int	cnt;

	cnt = 1;
	while (tkns->type != END)
	while (tkns->type != END)
	{
		if (tkns->type == PIPE)
		if (tkns->type == PIPE)
			cnt++;
		tkns++;
	}
	return (cnt);
	return (cnt);
}

//calculates input files for a pipe
int	calcins(t_tkn *tkns)
{
	int	cnt;

	cnt = 0;
	while (tkns->type != END && tkns->type != PIPE)
	while (tkns->type != END && tkns->type != PIPE)
	{
		if (tkns->type == LT || tkns->type == LLT)
		if (tkns->type == LT || tkns->type == LLT)
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
	while (tkns->type != END && tkns->type != PIPE)
	{
		if (tkns->type == GT || tkns->type == GGT)
		if (tkns->type == GT || tkns->type == GGT)
			cnt++;
		tkns++;
	}
	return (cnt);
}

/* calculates number of arguments for a single pipeline
we calculate args + cmd which should be argument zero
it calculates the first word token after the pipe
and any word preceeded by (another) word
*/
int	calcargs(t_tkn *tkns, char *envp[])
{
	int		cnt;
	t_tkn	*first;

	cnt = 0;
	first = tkns;
	while (tkns->type != END && tkns->type != PIPE)
	while (tkns->type != END && tkns->type != PIPE)
	{
		if (tkns->type == WORD && tkns == first && varvalid(tkns->val, envp))
			cnt++;
		if (tkns->type == WORD && tkns != first && (tkns - 1)->type == WORD
			&& varvalid(tkns->val, envp))
			cnt++;
		tkns++;
	}
	return (cnt);
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
	tbl->args = malloc((tbl->nargs + 1) * sizeof(char *));
	if (tbl->nins != 0)
		tbl->infiles = malloc(tbl->nins * sizeof(t_iof));
	if (tbl->nouts != 0)
		tbl->outfiles = malloc(tbl->nouts * sizeof(t_iof));
	if (tbl->args == NULL || (tbl->nins != 0 && tbl->infiles == NULL)
		|| (tbl->nouts != 0 && tbl->outfiles == NULL))
		errfree(err, tbl, free_rows, STP);
	tbl->curr_a = tbl->args;
	tbl->curr_i = tbl->infiles;
	tbl->curr_o = tbl->outfiles;
}
