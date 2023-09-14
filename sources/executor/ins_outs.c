/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_outs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/13 21:15:50 by mrubina          ###   ########.fr       */
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
			*fd = open(row->infiles[i].pth, O_RDONLY);
		if (*fd < 0)
		{
			row->flag = EO;
			errstr = row->infiles[i].pth;
			*fd = open("/dev/null", O_RDONLY);
			if (row->infiles[i].io == LLT)
				errstr = "here-document";
			if (row->pipeid == row->nrows - 1)
				err_handler(row->err, errstr, STP);
			else
				err_handler(row->err, errstr, CNT);
		}
		i++;
	}
}

/*
opening fds one by one
1) check if access permited (if denied we don't execute this pipe)
2) check if file exist and delete if not appended mode
3) open file
 */
int	outopen(t_cmdtable *r, int *fd, int stop)
{
	int	i;

	i = 0;
	while (i <= r->nouts - 1)
	{
		if (access(r->outfiles[i].pth, W_OK) == -1)
		{
			r->flag = EO;
			err_handler(r->err, r->outfiles[i].pth, stop);//for end cmd stop
			return (1);
		}
		if (access(r->outfiles[i].pth, F_OK) == 0 && r->outfiles[i].io == GT)
			unlink(r->outfiles[i].pth);
		if (r->outfiles[i].io == GGT)
			*fd = open(r->outfiles[i].pth, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			*fd = open(r->outfiles[i].pth, O_CREAT | O_WRONLY, 0644);
		if (*fd < 0)
			err_handler(r->err, r->outfiles[i].pth, stop);
		i++;
	}
	return (0);
}

//handling output before executing cmd
void	midouts(t_cmdtable *row, t_exedata *data)
{
	if (row->err->stop != STP && row->nouts != 0)
	{
		outopen(row, &data->outfd, CNT);
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
	if (row->err->stop != STP && row->nins != 0)
	{
		inopen(row, &data->infd, data->path[i]);
		data->pbreak = NB;
	}
	if (row->err->stop == NXT)
		row->err->stop = CNT;
}
