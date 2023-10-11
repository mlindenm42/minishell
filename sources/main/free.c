/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/11 21:02:12 by mrubina          ###   ########.fr       */
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
		// dprintf(2, "id%i\n", ((t_cmdtable *)row)->pipeid);
		// dprintf(2, "rowp%p\n", ((t_cmdtable *)row));
		// dprintf(2, "nextrowp%p\n", ((t_cmdtable *)row - 1));
		free_row(row);
		//dprintf(2, "my id%i\n", ((t_cmdtable *)row - 1)->pipeid);
		
		//if (((t_cmdtable *)row)->pipeid > 0)
			row = ((t_cmdtable *)row - 1);
		//else
		//	break;
		// dprintf(2, "rowp%p\n", row);
		//dprintf(2, "this is next row id%i\n", ((t_cmdtable *)row)->pipeid);
	}
	// dprintf(2, "lastrowp%p\n", row);
	// dprintf(2, "last id%i\n", ((t_cmdtable *)row)->pipeid);
	free_row(row);
}

/* void	free_rows(t_cmdtable *row)
{
	while (row->pipeid >= 0)
	{
		//dprintf(2, "my id%i\n", ((t_cmdtable *)row)->pipeid);
		//dprintf(2, "my id%i\n", ((t_cmdtable *)row - 1)->pipeid);
		free_row(row);
		//dprintf(2, "my id%i\n", ((t_cmdtable *)row - 1)->pipeid);
		//dprintf(2, "rowp%p\n", ((t_cmdtable *)row));
		//dprintf(2, "nextrowp%p\n", ((t_cmdtable *)row - 1));
		row--;
		//dprintf(2, "rowp%p\n", row);
		//dprintf(2, "my id%i\n", ((t_cmdtable *)row)->pipeid);
	}
} */

void	free_exedt(void *data)
{
	if (((t_exedata *)data)->id != NULL)
		free(((t_exedata *)data)->id);
	((t_exedata *)data)->id = NULL;
	if (((t_exedata *)data)->path != NULL)
		free(((t_exedata *)data)->path);
	((t_exedata *)data)->path = NULL;
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