/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/13 13:13:32 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//frees a row of a cmd table pointed by the argument
void	free_row(void *row)
{
	if (row != NULL)
	{
		//dprintf(2, "inf %p\n", ((t_cmdtable *)row)->infiles);
		if (((t_cmdtable *)row)->args != NULL)
			free(((t_cmdtable *)row)->args);
		if (((t_cmdtable *)row)->infiles != NULL)
			free(((t_cmdtable *)row)->infiles);
		if (((t_cmdtable *)row)->outfiles != NULL)
			free(((t_cmdtable *)row)->outfiles);
		if (((t_cmdtable *)row)->cmd != NULL)
			free_str(&((t_cmdtable *)row)->cmd);
		((t_cmdtable *)row)->args = NULL;
		((t_cmdtable *)row)->infiles = NULL;
		((t_cmdtable *)row)->outfiles = NULL;
	}
}

//frees a row and all previous rows in the table
void	free_rows(void *row)
{
	while (((t_cmdtable *)row)->pipeid > 0)
	{
		free_row(row);
		row = ((t_cmdtable *)row - 1);
	}
	free_row(row);
}

void	free_tbl(t_cmdtable **tbl)
{
	t_cmdtable *row;

	row = *tbl;
	while (row->pipeid < row->nrows - 1)
	{
		if (row->nins != 0)
			free_iof(row->infiles, row->nins);
		if (row->nouts != 0)
			free_iof(row->outfiles, row->nouts);
		free_row(row);
		row++;
	}
	if (row->nins != 0)
		free_iof(row->infiles, row->nins);
	if (row->nouts != 0)
		free_iof(row->outfiles, row->nouts);
	free_row(*tbl);
	free(*tbl);
	*tbl = NULL;
}

void	free_exedt(void *data)
{
	if (((t_exedata *)data)->id != NULL)
		free(((t_exedata *)data)->id);
	((t_exedata *)data)->id = NULL;
	free_arr(((t_exedata *)data)->path);
}

void	free_ptr(void *p)
{
	if (p != NULL)
		free(p);
	p = NULL;
}

void	free_tkns(t_tkn *tkns)
{
	t_tkn *token;

	token = tkns;
	while (token->type != END)
	{
		if (token->type == WORD)
			free_ptr(token->val);
		token++;
	}
	free (tkns);
}

void	free_iof(t_iof *arr, int n)
{
	int i;

	//dprintf(2, "in f %p\n", arr);

	i = 0;
	while (i < n)
	{
		free_str(&arr->file);
		free(arr->file);
		arr++;
		i++;
	}
}