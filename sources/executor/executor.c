/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/15 16:19:29 by mrubina          ###   ########.fr       */
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

//setting input
void	setin(t_cmdtable *row, t_exedata *data, int *i, t_errdata *err)
{
	if (row->nins != 0)
	{
		inopen(row, &data->infd, data->path[0], err);
		redir_close(data->infd, 0, err);
		if (row->eflag == ERR && row->nrows > 1)
			(*i)++;
	}
	else
		data->infd = data->intmpfd;
}

//allocation and saving
/*
allocating and initiolizing data members
execuing heredoc inputs
setting first input
 */
static int	data_init(t_cmdtable *tbl, t_exedata *data, int *i, t_errdata *err)
{
	data->pbreak = NB;
	data->path = NULL;
	data->id = malloc(sizeof(pid_t) * tbl->nrows);
	if (data->id == NULL)
	{
		errfree(err, data->id, NULL, STP);
		return (1);
	}
	data->intmpfd = dup(0);
	if (data->intmpfd < 0)
		err_handler(err, NULL, CNT);
	data->outtmpfd = dup(1);
	if (data->outtmpfd < 0)
		err_handler(err, NULL, CNT);
	if (heredoc(tbl, data, err) == 1)
		return (1);
	setin(tbl, data, i, err);
	return (0);
}

/*
 wait for the end of cmds
 set exitstatus
 restore stdin and stdout
 delete temporary files
 free what was allocated
 */
void	finish(t_cmdtable *tbl, t_exedata *data, t_errdata *err)
{
	int		i;
	char	*errstr;

	i = 0;
	while (i <= tbl->nrows - 1)
	{
		errstr = ft_itoa(data->id[i]);
		if (tbl[i].eflag != ERR && waitpid(data->id[i], &data->status, 0) == -1)
			err_handler(err, errstr, CNT);
		if (errstr != NULL)
			free(errstr);
		i++;
	}
	if (tbl[tbl->nrows - 1].eflag != ERR)
		err->stat = WEXITSTATUS(data->status);
	redir_close(data->intmpfd, 0, err);
	redir_close(data->outtmpfd, 1, err);
	i = 0;
	while (i <= tbl->nrows - 1)
	{
		if (data->path[i] != NULL)
			unlink(data->path[i]);
		i++;
	}
	free_exedt(data);
}

//set output for the last command
int	lastcmd(t_cmdtable *row, t_exedata *data, char *envp[], t_errdata *err)
{
	outopen(row, &data->outfd, NXT, err);
	if (row->nouts == 0)
		data->outfd = dup(data->outtmpfd);
	if (row->pipeid != 0 && data->pbreak != BR && (row - 1)->eflag != ERR)
		redir_close(data->infd, 0, err);
	if (err->stop != NXT)
	{
		if (row->cmd != NULL && env_change(row->cmd, row->nrows))
		{
			exe_builtin(row, envp, err, 1);
			row->eflag = ERR;
		}
		else
			create_child(row, envp, err);
	}
	return (0);
}

int	executor(t_cmdtable *tbl, char *envp[], t_errdata *err)
{
	t_exedata	data;
	int			i;

	i = 0;
	if (data_init(tbl, &data, &i, err) == 1)
		return (1);
	err->edata = &data;
	while (i <= tbl->nrows - 2)
	{
		if (i != 0 && data.pbreak != BR && tbl[i - 1].eflag != ERR)
			redir_close(data.infd, 0, err);
		data.pbreak = NB;
		midouts(&tbl[i], &data, err);
		if (create_pipe(&data, err) == STP)
			return (1);
		if (err->stop == CNT)
			create_child(&tbl[i], envp, err);
		setnextin(&tbl[i + 1], &data, err, i + 1);
		i++;
	}
	lastcmd(&tbl[i], &data, envp, err);
	finish(tbl, &data, err);
	err->edata = NULL;
	return (0);
}
