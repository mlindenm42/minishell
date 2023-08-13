/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/12 13:58:56 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//for now it frees only a row of a cmd table pointed by the argument
//to be completed later
void	err_handler(t_cmdtable *tbl)
{
	if (tbl != NULL)
	{
		if (tbl->args != NULL)
			free(tbl->args);
		if (tbl->infiles != NULL)
			free(tbl->infiles);
		if (tbl->outfiles != NULL)
			free(tbl->outfiles);
	}
	perror("minishell");
}
