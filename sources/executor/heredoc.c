/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 22:24:36 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* checking delimiter after each newine
buffer variants
|text\n     | |delimiter\n| - don't write into the file  !!!
|texttexttex| |delimiter\n| - write the whole buffer to the file !!!
|texttexttex| - write the whole buffer to the file
|text\n     | - write the part of the buffer including \n
*/

//generates temporary file name based on row number
static char	*genpath(int i, t_errdata *err)
{
	char	*n;
	char	*fpath;

	fpath = NULL;
	n = ft_itoa(i, err);
	if (n != NULL)
		fpath = ft_strjoin("sources/obj/tmp", n, err);
	return (fpath);
}

static int	stdintofd(char *dlm, int filefd)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (ft_strcmp(input, dlm) == 0)
			break ;
		ft_putendl_fd(input, filefd);
		free(input);
		input = NULL;
	}
	return (0);
}

//scanning inputs for here_docs
static void	inputscan(t_exedata *data, t_cmdtable *row, t_errdata *err, int i)
{
	int	k;
	int	fd;

	k = 0;
	while (k <= row->nins - 1)
	{
		if (row->infiles[k].io == LLT)
		{
			if (data->path[i] == NULL)
				data->path[i] = genpath(i, err);
			if (data->path[i] != NULL)
			{
				if (access(data->path[i], F_OK) == 0)
					unlink(data->path[i]);
				fd = open(data->path[i], O_CREAT | O_RDWR, 0644);
				if (fd >= 0)
				{
					if (stdintofd(row->infiles[k].file, fd) == 1)
						err_handler(err, "here_document", CNT);
					close(fd);
				}
			}
		}
		k++;
	}
}

int	heredoc(t_cmdtable *tbl, t_exedata *data, t_errdata *err)
{
	int	i;

	i = 0;
	data->path = create_pile(&err->gc, sizeof(char *), (tbl->nrows + 1));
	if (data->path == NULL)
	{
		errfree(err, &data, &free_exedt, CNT);
		return (1);
	}
	data->path[tbl->nrows] = NULL;
	while (i <= tbl->nrows - 1)
	{
		data->path[i] = NULL;
		inputscan(data, &tbl[i], err, i);
		i++;
	}
	return (0);
}
