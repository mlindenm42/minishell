/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 22:26:17 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//frees a row of a cmd table pointed by the argument
void	free_row(void *row)
{
	//if (row != NULL)
	//{
	//	//dprintf(2, "inf %p\n", ((t_cmdtable *)row)->infiles);
	//	if (((t_cmdtable *)row)->args != NULL)
	//		free(((t_cmdtable *)row)->args);
	//	if (((t_cmdtable *)row)->infiles != NULL)
	//		free(((t_cmdtable *)row)->infiles);
	//	if (((t_cmdtable *)row)->outfiles != NULL)
	//		free(((t_cmdtable *)row)->outfiles);
	//	if (((t_cmdtable *)row)->cmd != NULL
	//		&& ((t_cmdtable *)row)->path_flag == 1)
	//		free_str(&((t_cmdtable *)row)->cmd);
	//	((t_cmdtable *)row)->args = NULL;
	//	((t_cmdtable *)row)->infiles = NULL;
	//	((t_cmdtable *)row)->outfiles = NULL;
	//	free(row);
	//}
}

//frees a row and all previous rows in the table
void	free_rows(void *row)
{
	//while (((t_cmdtable *)row)->pipeid > 0)
	//{
	//	free_row(row);
	//	row = ((t_cmdtable *)row - 1);
	//}
	//free_row(row);
}


void	free_tbl(t_errdata *err)
{
	//t_cmdtable *row;

	//row = err->tbl;
	//while (row->pipeid < row->nrows - 1)
	//{
	//	// if (row->nins != 0)
	//	// 	//free_iof(row->infiles, row->nins);
	//	// 	free(row->infiles);
	//	// if (row->nouts != 0)
	//	// 	//free_iof(row->outfiles, row->nouts);
	//	// 	free(row->outfiles);
	//	free_row(row);
	//	row++;
	//}
	//// if (row->nins != 0)
	//// 	free(row->infiles);
	//// 	//free_iof(row->infiles, row->nins);
	//// if (row->nouts != 0)
	//// 	free(row->outfiles);
	//	//free_iof(row->outfiles, row->nouts);
	//free_row(err->tbl);
	////free(err->tbl);
	//err->tbl = NULL;
}

void	free_patharr(char **arr, int n)
{
	//int	i;

	//i = 0;
	//while (i < n)
	//{
	//	if (arr[i] != NULL)
	//		free(arr[i]);
	//	arr[i] = NULL;
	//	i++;
	//}
}

void	free_exedt(void *data)
{
	//if (((t_exedata *)data) != NULL)
	//{
	//	if (((t_exedata *)data)->id != NULL)
	//		free(((t_exedata *)data)->id);
	//	((t_exedata *)data)->id = NULL;
	//	if (((t_exedata *)data)->path != NULL)
	//	{
	//		free_patharr(((t_exedata *)data)->path, ((t_exedata *)data)->nrows);
	//		free(((t_exedata *)data)->path);
	//	}
	//	((t_exedata *)data)->path = NULL;
	//}
}

/* void	free_exedt1(t_exedata*data, int n)
{
	if (data->id != NULL)
		free(data->id);
	data->id = NULL;
	if (data->path != NULL)
	{
		while ()
	}
	data->path = NULL;
} */

void	free_ptr(void *p)
{
	//if (p != NULL)
	//	free(p);
	//p = NULL;
}

void	free_iof(t_iof *arr, int n)
{
	//int	i;

	//i = 0;
	//while (i < n)
	//{
	//	free(arr->file);
	//	arr++;
	//	i++;
	//}
}

void freeall(t_errdata *err)
{
	//free_exedt(err->edata);
	//free_str(&(err->statstr));
	// free_tokens();
	// free_tbl(err);
}

void freecycle(t_errdata *err)
{
	//free_exedt(err->edata);
	//free_tokens();
	// free_tbl(err);
}
