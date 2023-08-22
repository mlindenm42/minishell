/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/22 13:57:55 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->token, tkn->val);
//printf("nd token%i, %s\n", tkn->token, tkn->val);
//printf("%i\n", pipe_cnt);
//redirecting file descriptor to stdin/stddout and closing it
void	redir_close(int fd, int stdfd, int *status)
{
	if (dup2(fd, stdfd) == -1)
		//error_handler(ERR, "", status);
	//if (close(fd) == -1)
	close(fd);
		//error_handler(ERR, "", status);
}

int	outopen(t_cmdtable *row, int *fd, int *flag)
{
	int	i;
	//int	status;

	i = 0;
	while (i <= row->nouts - 1)
	{
		if (access(row->outfiles[i].file, W_OK) == -1 && errno == EACCES)
		{
			*flag = EO;
			perror("");
			//return (0);
		}
		//error_handler(EACCES, outfile, status);
		if (access(row->outfiles[i].file, F_OK) == 0 && row->outfiles[i].io == GT)
			unlink(row->outfiles[i].file);
		if (row->outfiles[i].io == GGT)
			*fd = open(row->outfiles[i].file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			*fd = open(row->outfiles[i].file, O_CREAT | O_WRONLY, 0644);
		if (*fd < 0)
			perror("");
			//	error_handler(ERR, "", status);
		i++;
	}
	return (0);
}

void	create_pipe(int *pipefd, int *status)
{
	//if (pipe(pipefd) == -1)
	pipe(pipefd);
		//error_handler(ERR, "", status);
}

int	wait_end(t_exdata data, int pipes)
{
	int	i;

	i = 0;
	while (i <= pipes - 1)
	{
		if (waitpid(data.id[i], &data.status, 0) == -1)
			//error_handler(ERR, "", status);
		i++;
	}
	return (WEXITSTATUS(data.status));
}

	/* handling infiles
	in case of an error at least in one of the files process doesn't start in this pipeline
	the next pipeline receives an empty input
	in case of no error only the last infile is used!!!
	for each pipe explicit input of that pipe overrides output from the previous pipe
	*/	
int	inopen(t_cmdtable *row, int *fd, int *flag)
{
	int	i;

	i = 0;
	while (i <= row->nins - 1)
	{
		*fd = open(row->infiles[i].file, O_RDONLY);
		if (*fd < 0)
		{
			*flag = EO;
			*fd = open("/dev/null", O_RDONLY);
			perror("minishell");
			return (0);
		}
		i++;
	}
	return (0);
}

/* creates child process, redirects output to the next pipe and executes command */
void create_child(t_cmdtable *row, char *envp[], t_exdata *data, int flag)
{
	data->id[row->pipeid] = fork();
	//if (id == -1)
	//	error_handler(ERR, "", status);
	if (data->id[row->pipeid] == 0)
	{
		data->status = 0;
		if (row->pipeid != row->nrows - 1)
		{
			close(data->pipefds[row->pipeid * 2]);
			ft_putnbr_fd(flag, 2);
			ft_putchar_fd('\n', 2);
			if (flag != BR)
				dup2(data->pipefds[row->pipeid * 2 + 1], 1);
			//if (close(pipefd[0]) == -1 || dup2(pipefd[1], 1) == -1)
			//	error_handler(ERR, "", &status);
		}
		if (execve(row->cmd, row->args, envp) == -1)
			perror("exe err");
		//	error_handler(NFOUND, cmd_path, &status);
	}
}
