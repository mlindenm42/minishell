/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_outs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/17 20:35:50 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* handling infiles
	in case of an error at least in one of the files process
	doesn't start in this pipeline
	the next pipeline receives an empty input
	in case of no error only the last infile is used
	for each pipe explicit input of that pipe overrides output
	from the previous pipe
*/
void	inopen(t_cmdtable *row, int *fd, char *hdpath)
{
	int		i;
	char	*errstr;

	i = 0;
	while (i <= row->nins - 1)
	{
		if (row->infiles[i].io == LLT)
			*fd = open(hdpath, O_RDONLY);
		else
			*fd = open(row->infiles[i].file, O_RDONLY);
		if (*fd < 0)
		{
			row->eflag = ERR;
			errstr = row->infiles[i].file;
			*fd = open("/dev/null", O_RDONLY);
			if (row->infiles[i].io == LLT)
				errstr = "here-document";
			err_handler(row->err, errstr, CNT);
		}
		i++;
	}
}

//sets error flag for the pipeline and prints out error
static void	seterr(t_cmdtable *row, int i, int stop)
{
	row->eflag = ERR;
	err_handler(row->err, row->outfiles[i].file, stop);
}

/*
opening fds one by one
1) check if access permited (if denied we don't execute this pipe)
(we catch it at the start because we don't want it to be deleted)
2) check if file exist and delete if not appended mode
3) open file
 */
int	outopen(t_cmdtable *row, int *fd, int stop)
{
	int	i;

	i = 0;
	while (i <= row->nouts - 1)
	{
		if ((access(row->outfiles[i].file, W_OK) == -1 && errno == EACCES)
			|| wrongvar(row->outfiles[i].file))
		{
			seterr(row, i, stop);
			return (1);
		}
		if (access(row->outfiles[i].file, F_OK) == 0
			&& row->outfiles[i].io == GT)
			unlink(row->outfiles[i].file);
		if (row->outfiles[i].io == GGT)
			*fd = open(row->outfiles[i].file, O_CREAT | O_WRONLY
					| O_APPEND, 0644);
		else
			*fd = open(row->outfiles[i].file, O_CREAT | O_WRONLY, 0644);
		if (*fd < 0)
			seterr(row, i, stop);
		i++;
	}
	return (0);
}

//handling output before executing cmd
void	midouts(t_cmdtable *row, t_exedata *data)
{
	if (row->nouts != 0)
	{
		outopen(row, &data->outfd, NXT);
		data->pbreak = BR;
		if (row->err->stop != NXT)
		{
			if (access(row->cmd, F_OK) == -1 || access(row->cmd, X_OK) == -1)
				data->pbreak = NB;
		}
		if (row->err->stop == NXT)
			close(0);
	}
}

/*
	setting input for next command
 */
void	setnextin(t_cmdtable *row, t_exedata *data, int i)
{
	if (row->err->stop == NXT && row->nins == 0)
		data->infd = open("/dev/null", O_RDONLY);
	if (row->nins != 0)
	{
		inopen(row, &data->infd, data->path[i]);
		data->pbreak = NB;
	}
	if (row->err->stop == NXT)
		row->err->stop = CNT;
}
