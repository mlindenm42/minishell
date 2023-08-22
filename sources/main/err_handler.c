/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/22 19:33:09 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//for now it frees only a row of a cmd table pointed by the argument
//to be completed later

void	err_handler(t_errdata *err, void *struc, void (*delstruct)(void *))
{
	//if (struc == NULL)
	perror(err->name);
}

//frees a row of a cmd table pointed by the argument
void	free_row(void *row)
{
	if (row != NULL)
	{
		if (((t_cmdtable*)row)->args != NULL)
			free(((t_cmdtable*)row)->args);
		if (((t_cmdtable*)row)->infiles != NULL)
			free(((t_cmdtable*)row)->infiles);
		if (((t_cmdtable*)row)->outfiles != NULL)
			free(((t_cmdtable*)row)->outfiles);
		((t_cmdtable*)row)->args = NULL;
		((t_cmdtable*)row)->infiles = NULL;
		((t_cmdtable*)row)->outfiles = NULL;
	}
}

//frees a row and all previous rows in the table
void	free_rows(void *row)
{
	while (((t_cmdtable*)row)->pipeid >= 0)
	{
		free_row(row);
		row--;
	}
}
