/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/13 21:50:56 by mrubina          ###   ########.fr       */
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

int	create_pipe(t_exedata *data, t_errdata *err)
{
	int	pp[2];

	if (err->stop == CNT && data->pbreak != BR)
	{
		if (pipe(pp) == -1)
			errfree(err, data, &free_exedt, STP);
		data->infd = pp[0];
		data->outfd = pp[1];
	}
	//in case of error free data
	return (err->stop);
}

/* redirects stdout to the pipe, creates child process and executes command */
int	create_child(t_cmdtable *row, char *envp[], t_exedata *data)
{
	redir_close(data->outfd, 1, row->err);
	data->id[row->pipeid] = fork();
	if (data->id[row->pipeid] == -1)
		err_handler(row->err, NULL, NXT);
	if (data->id[row->pipeid] == 0)
	{
		data->status = 0;
		if (row->err->stop != STP && execve(row->cmd, row->args, envp) == -1)
			cmderr(row->err, row->cmd, CNT);
	}
	return (row->err->stop);
}
