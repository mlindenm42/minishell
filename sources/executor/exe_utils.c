/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/19 19:52:15 by mrubina          ###   ########.fr       */
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

//open input file
int	inopen(char *infile, int *status)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		//error_handler(ENOENT, infile, status);
		fd = open("/dev/null", O_RDONLY);
	}
	return (fd);
}

int	outopen(char *outfile, int *status)
{
	int	fd;

	//if (access(outfile, W_OK) == -1 && errno == EACCES)
		//error_handler(EACCES, outfile, status);
	if (access(outfile, F_OK) == 0)
		unlink(outfile);
	fd = open(outfile, O_CREAT | O_WRONLY, 0644);
	//if (fd < 0)
	//	error_handler(ERR, "", status);
	return (fd);
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

int createfork(t_cmdtable *row, char *envp[], t_exdata *data)
{
		//printf("p%i\n", data->status);
		//printargs(row.args, row.nargs);
		//printf(" n%i\n", row.nargs);
		//execve(row->cmd, row->args, envp);
		//execve(tbl->cmd, tbl->args, envp);
	data->id[row->pipe] = fork();
	//ft_putendl_fd(row->cmd, 2);
	//ft_putnbr_fd(data.id[row.pipe], 2);
	//if (id == -1)
	//	error_handler(ERR, "", status);
	//ft_putnbr_fd(data.id[row.pipe], 2);
	if (data->id[row->pipe] == 0)
	{
		//exit(0);
		data->status = 0;
		//execve(row->cmd, row->args, envp);
		if (row->pipe != row->nrows - 1)
		{
			close(data->pipefds[row->pipe * 2]);
			dup2(data->pipefds[row->pipe * 2 + 1], 1);
			//if (close(pipefd[0]) == -1 || dup2(pipefd[1], 1) == -1)
			//	error_handler(ERR, "", &status);
		}
		//execve(row.cmd, row.args, envp);
		//ft_putnbr_fd(data.id[row.pipe], 2);
		if (execve(row->cmd, row->args, envp) == -1)
			perror("exe err");
		//	error_handler(NFOUND, cmd_path, &status);
	}
	//exit(0);
	return (data->status);
}