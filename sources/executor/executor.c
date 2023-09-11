/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/11 23:38:18 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->token, tkn->val);
//printf("nd token%i, %s\n", tkn->token, tkn->val);
//printf("%i\n", pipes);
//ft_putnbr_fd(flag, 2);
//ft_putchar_fd('\n', 2);
//dprintf(2, "my id%i\n", data.id[i]);

//takes command table and executes commmand
/* int		pipe;
	char	*cmd;
	char	**args;
	t_iof	*infiles;
	t_iof	*outfiles;
	char	**curr_a;
	t_iof	*curr_i;
	t_iof	*curr_o;
	int		nargs;
	int		nins;
	int		nouts; */


//allocation and saving
int exec_init(t_cmdtable *tbl, t_exedata *data)
{
	data->pbreak = NB;
	data->id = malloc(sizeof(pid_t)*tbl->nrows);
	if (data->id == NULL)
	{
		errfree(tbl->err, &data, &free_exedt, STP);
		return (1);
	}
	data->intmpfd = dup(0);
	if (data->intmpfd < 0)
		err_handler(tbl->err, NULL, CNT);
	data->outtmpfd = dup(1);
	if (data->outtmpfd < 0)
		err_handler(tbl->err, NULL, CNT);
	return (0);
}

// handling mid outs
void midouts(t_cmdtable *row, t_exedata *data)
{
	if (row->err->stop != STP && row->nouts != 0)
	{
		//setting output file or std
		outopen(row, &data->outfd, &data->pbreak);
		data->pbreak = BR;
			//predict command not executed also do it for the last one !!!
			//break is cancelled in case of a cmd error
		if (row->err->stop != NXT)
		{
			if (access(row->cmd, F_OK) == -1 || access(row->cmd, X_OK) == -1)
				data->pbreak = NB;
		}
		if (row->err->stop == NXT)
			close(0);
	}
}

void setin(t_cmdtable *row, t_exedata *data, int *i)
{
	if (row->nins != 0)
	{
		inopen(row, &data->infd, data->path[0]);
		redir_close(data->infd, 0, row->err);
		if (row->flag == EO && row->nrows > 1)
			(*i)++;
	}
	else
		data->infd = data->intmpfd;
}

//setting input for next command in case of no break
void setnextin(t_cmdtable *row, t_exedata *data, int i)
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

void finish(t_cmdtable *tbl, t_exedata *data)
{
	int		i;
	char	*errstr;

	i = 0;
	while (i <= tbl->nrows - 1)
	{
		errstr = ft_itoa(data->id[i]);
		if (tbl[i].flag != EO && waitpid(data->id[i], &data->status, 0) == -1)
			err_handler(tbl->err, errstr, CNT);
		if (errstr != NULL)
			free(errstr);
		i++;
	}
	tbl->err->stat = WEXITSTATUS(data->status);
	redir_close(data->intmpfd, 0, tbl->err);
	redir_close(data->outtmpfd, 1, tbl->err);
	i = 0;
	while (i <= tbl->nrows - 1)
	{
		if (data->path[i] != NULL)
			unlink(data->path[i]);
		i++;
	}
	free(data->path);
	data->path = NULL;
}

int	executor(t_cmdtable *tbl, char *envp[], t_errdata *err)
{
	t_cmdtable	*row;
	t_exedata	data;
	int			i;
	char		*buf;
	int			fd;

	i = 0;
	if (exec_init(tbl, &data) == 1)
		return (1);
	if (heredoc(tbl, &data) == 1)
		return (1);
	setin(tbl, &data, &i);
	while (err->stop != STP && i <= tbl->nrows - 2)
	{
		if (i != 0 && data.pbreak != BR && tbl[i - 1].flag != EO)
			redir_close(data.infd, 0, err);//input for cur cmd is set
		if (data.pbreak != NB)
			data.pbreak = NB;
		midouts(&tbl[i], &data);
		if (create_pipe(&data.infd, &data.outfd, &data.pbreak, err) == STP)
			return (1);
		//output redirection and execution
		if (err->stop == CNT)
		{
			redir_close(data.outfd, 1, err);//redir stdout goes into pipe
			create_child(&tbl[i], envp, &data, &data.pbreak);
		}
		setnextin(&tbl[i + 1], &data, i + 1);
		i++;
	}
	if (err->stop == STP)
		return(1);
	outopen(&tbl[i], &data.outfd, NULL);
	if (tbl[i].nouts == 0)
		data.outfd = dup(data.outtmpfd);
	if (i != 0 && data.pbreak != BR)
		redir_close(data.infd, 0, err);
	redir_close(data.outfd, 1, err);
	create_child(&tbl[i], envp, &data, &data.pbreak);
	finish(tbl, &data);
	return (0);
}
