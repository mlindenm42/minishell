/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/11 23:26:43 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->token, tkn->val);
//printf("nd token%i, %s\n", tkn->token, tkn->val);
//printf("%i\n", pipes);

//redirecting file descriptor to stdin/stddout and closing it
void	redir_close(int fd, int stdfd, t_errdata *err)
{
	if (err->stop != STP && dup2(fd, stdfd) == -1)
		err_handler(err, NULL, CNT);
	if (err->stop == CNT && close(fd) == -1)
		err_handler(err, NULL, CNT);
}

/*
opening fds one by one
1) check if access permited (if denied we don't execute this pipe)
2) check if file exist and delete if not appended mode
3) open file
flag equals NULL for the last pipe
try without flags!!!
 */
int	lastcmd(t_cmdtable *row)
{
	return (row->pipeid == row->nrows - 1);
}

int	outopen(t_cmdtable *row, int *fd, int *flag)
{
	int	i;
	int stop;

	i = 0;
	if (row->pipeid == row->nrows - 1)
		stop = STP;
	else
		stop = CNT;
	while (i <= row->nouts - 1)
	{
		if (access(row->outfiles[i].file, W_OK) == -1)
		{
			row->flag = EO;
			stop = NXT;
			//if (errno == EACCES)
			err_handler(row->err, row->outfiles[i].file, stop);//check EACCESS!!!
			return (row->err->stop);
		}
		if (access(row->outfiles[i].file, F_OK) == 0 && row->outfiles[i].io == GT)
			unlink(row->outfiles[i].file);
		if (row->outfiles[i].io == GGT)
			*fd = open(row->outfiles[i].file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			*fd = open(row->outfiles[i].file, O_CREAT | O_WRONLY, 0644);
		if (*fd < 0)
			err_handler(row->err, row->outfiles[i].file, stop);
		i++;
	}
	return (row->err->stop);
}

int	create_pipe(int *infd, int *outfd, int *pbreak, t_errdata *err)
{
	int	pp[2];

	if (err->stop == CNT && *pbreak != BR)
	{
		if (pipe(pp) == -1)
			err_handler(err, NULL, CNT);
		if (infd != NULL)
			*infd = pp[0];//pipe output // cmd in
		if (outfd != NULL)
			*outfd = pp[1];//pipe input // cmd out
	}
	return(err->stop);
}
	/* handling infiles
	in case of an error at least in one of the files process doesn't start in this pipeline
	the next pipeline receives an empty input
	in case of no error only the last infile is used!!!
	for each pipe explicit input of that pipe overrides output from the previous pipe
	*/
int	inopen(t_cmdtable *row, int *fd, char *hdpath)
{
	int	i;
	char *errstr;

	i = 0;
	while (i <= row->nins - 1)
	{
		if (row->infiles[i].io == LLT)
			*fd = open(hdpath, O_RDONLY);
		else
			*fd = open(row->infiles[i].file, O_RDONLY);
		if (*fd < 0)
		{
			row->flag = EO;
			errstr = row->infiles[i].file;
			*fd = open("/dev/null", O_RDONLY);
			errstr = row->infiles[i].file;
			if (row->infiles[i].io == LLT)
				errstr = "here-document";
			if (row->pipeid == row->nrows - 1)
				err_handler(row->err, errstr, STP);
			else
				err_handler(row->err, errstr, CNT);
			return (row->err->stop);
		}
		i++;
	}
	return (row->err->stop);
}

/* creates child process, redirects output to the next pipe and executes command */
int create_child(t_cmdtable *row, char *envp[], t_exedata *data, int *flag)
{
	data->id[row->pipeid] = fork();
	if (data->id[row->pipeid] == -1)
		err_handler(row->err, NULL, NXT);
	if (data->id[row->pipeid] == 0)
	{
		data->status = 0;
		if (row->pipeid != row->nrows - 1)
		{
			//if (row->pipeid == 0 && row->infiles->io != LLT)
/* 			if (row->infiles->io == LLT)
				{
					close(0);
					//dprintf(2, "cls");
				} */
		}
		if (row->err->stop != STP && execve(row->cmd, row->args, envp) == -1)
			{
				//if (row->infiles->io != LLT)
				cmderr(row->err, row->cmd, CNT);
			}
	}
	return (row->err->stop);
}
