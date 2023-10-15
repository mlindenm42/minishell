/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/15 19:55:28 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//frees a row of a cmd table pointed by the argument
void	free_row(void *row, int path_flag)
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
		if (((t_cmdtable *)row)->cmd != NULL && path_flag == 1)
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
		free_row(row, 0);
		row = ((t_cmdtable *)row - 1);
	}
	free_row(row, 0);
}


void	free_tbl(t_errdata *err)
{
	t_cmdtable *row;

	row = err->tbl;
	while (row->pipeid < row->nrows - 1)
	{
		if (row->nins != 0)
			free_iof(row->infiles, row->nins);
		if (row->nouts != 0)
			free_iof(row->outfiles, row->nouts);
		free_row(row, err->path_flag);
		row++;
	}
	if (row->nins != 0)
		free_iof(row->infiles, row->nins);
	if (row->nouts != 0)
		free_iof(row->outfiles, row->nouts);
	free_row(err->tbl, err->path_flag);
	free(err->tbl);
	err->tbl = NULL;
}

void	free_patharr(char **arr)
{
	char	**str;

	if (arr != NULL)
	{
		str = arr;
		while (str != NULL && *str != NULL)
		{
			dprintf(2, "arr in %s\n", *str);
			if (*str != NULL)
				free(*str);
			else
				break;
			dprintf(2, "arr in fghfh %s\n", *str);
			*str = NULL;
			str++;
		}
		//dprintf(2, "arr inl %p\n", arr);
		//exit(0);
		free(arr);
	}
}



void	free_exedt(void *data)
{
	if (((t_exedata *)data)->id != NULL)
		free(((t_exedata *)data)->id);
	((t_exedata *)data)->id = NULL;
	dprintf(2, "arr %p\n", ((t_exedata *)data)->path);
	if (((t_exedata *)data)->path != NULL)
		free_patharr(((t_exedata *)data)->path);
	((t_exedata *)data)->path = NULL;
}

void	free_exedt1(t_exedata *data)
{
	//if (data->id != NULL)
		dprintf(2, "test %p\n", data);
	// 	free(data->id);
	//data->id = NULL;
	//if (data->path != NULL)
		//dprintf(2, "test\n");
		//free_exedt
		//free_arr(data->path);
	//data->path = NULL;
}

void	free_ptr(void *p)
{
	if (p != NULL)
		free(p);
	p = NULL;
}

void	free_iof(t_iof *arr, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(arr->file);
		arr++;
		i++;
	}
}

void freeall(t_errdata *err)
{
	free_exedt(err->edata);
	free_str(&(err->statstr));
	free_tokens();
	free_tbl(err);
}
