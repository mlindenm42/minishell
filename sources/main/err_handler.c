/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/11 22:25:48 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//for now it frees only a row of a cmd table pointed by the argument
//to be completed later

// free structure and output error
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop)
{
	char	*pref;

	err->stop = stop;
	err->stat = 1;
	if (del != NULL && struc != NULL)
		del(struc);
	perror("minishell");
}

//output error extending its description if needed
void	err_handler(t_errdata *err, char *str, int stop)
{
	char	*pref;

	err->stop = stop;
	err->stat = 1;

	if (str != NULL)
	{
		pref = ft_strjoin("minishell: ", (char *)str);
		perror(pref);
		free(pref);
		pref = NULL;
	}
	else
		perror("minishell");
}

void	cmderr(t_errdata *err, void *cmd, int stop)
{
	char	*txt;
	char	*tmp;

	err->stop = stop;
	err->stat = 126;
	tmp = ft_strjoin("minishell: ", (char *)cmd);
	if (ft_strchr(cmd, '/') == NULL)
	{
		txt = ft_strjoin(tmp, ": command not found");
		ft_putendl_fd(txt, 2);
		free(txt);
		err->stat = 127;
	}
	else
		perror(tmp);
	free(tmp);
	exit(err->stat);
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

void	free_exedt(void *data)
{
	if (((t_exedata*)data)->id != NULL)
		free(((t_exedata*)data)->id);
	((t_exedata*)data)->id = NULL;
}



/* void	addtext(void *fpath)
{
	//char	*t;
	err->errtext = ft_strjoin(err->errtext, (char *)fpath);
} */