/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/11 21:25:06 by mrubina          ###   ########.fr       */
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
static char	*genpath(int i)
{
	char	*n;
	char	*fpath;

	fpath = NULL;
	n = ft_itoa(i);
	if (n != NULL)
	{
		fpath = ft_strjoin("sources/obj/tmp", n);
		free(n);
	}
	return (fpath);
}

static int	nlupdate(char *cur, int isdlm, int prevnl, int flag)
{
	if (flag == 1 && *cur == '\n' && isdlm == TRUE)
		return (TRUE);
	else if (flag == 0)
	{
		if (*cur != '\n')
			return (FALSE);
		if (*cur == '\n' && isdlm == FALSE)
			return (TRUE);
	}
	return (prevnl);
}

/*
reads from stdin untill delimiter and writes into a file
prevnl is TRUE if previous buffer ended with newline
 */
static int	stdintofd(char *dlm, int filefd)
{
	char	*buf;
	char	*cur;
	int		size;
	int		prevnl;
	int		isdlm;

	prevnl = TRUE;
	isdlm = FALSE;
	size = ft_strlen(dlm) + 1;
	buf = malloc(size * sizeof(char));
	if (buf == NULL)
		return (1);
	cur = buf;
	write(1, "> ", 3);
	while (isdlm == 0 || *(buf + size - 1) != '\n' || prevnl == 0)
	{
		prevnl = nlupdate(cur, isdlm, prevnl, 1);
		cur = readbuf(buf, size);
		isdlm = (ft_strncmp(buf, dlm, size - 1) == 0);
		wrtofile((isdlm == TRUE && prevnl == TRUE), filefd, cur, buf);
		prevnl = nlupdate(cur, isdlm, prevnl, 0);
	}
	free(buf);
	buf = NULL;
	return (0);
}

//scanning inputs for here_docs
static void	inputscan(t_exedata *data, t_cmdtable *row, int i)
{
	int	k;
	int	fd;

	k = 0;
	while (k <= row->nins - 1)
	{
		if (row->infiles[k].io == LLT)
		{
			if (data->path[i] == NULL)
				data->path[i] = genpath(i);
			if (data->path[i] != NULL)
			{
				if (access(data->path[i], F_OK) == 0)
					unlink(data->path[i]);
				fd = open(data->path[i], O_CREAT | O_RDWR, 0644);
				if (fd >= 0)
				{
					if (stdintofd(row->infiles[k].file, fd) == 1)
						err_handler(row->err, "here_document", CNT);
					close(fd);
				}
			}
		}
		k++;
	}
}

int	heredoc(t_cmdtable *tbl, t_exedata *data)
{
	int	i;

	i = 0;
	data->path = malloc(sizeof(char *) * tbl->nrows);
	if (data->path == NULL)
	{
		errfree(tbl->err, &data, NULL, STP);
		return (1);
	}
	while (i <= tbl->nrows - 1)
	{
		data->path[i] = NULL;
		inputscan(data, &tbl[i], i);
		i++;
	}
	return (0);
}
