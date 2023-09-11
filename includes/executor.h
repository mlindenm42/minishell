/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/11 22:25:30 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file we have functions used only in the executor
*/
#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_exedata
{
	int		infd;
	int		outfd;
	int		intmpfd;
	int		outtmpfd;
	int		status;
	int		pbreak;
	pid_t	*id;
	char	**path;
}	t_exedata;

//constants showing how ins/outs in the middle pipes break the stream
# define NB 1
# define BR 2
# define EO 3

//constants showing what to do after error stop/continue/ go to the next pipe
# define STP 5
# define CNT 6
# define NXT 7

int	heredoc	(t_cmdtable *tbl, t_exedata *data);
void	redir_close(int fd, int stdfd,  t_errdata *err);
//int	create_pipe(int *pipefd, int *status, t_errdata *err);
int	create_pipe(int *infd, int *outfd, int *status, t_errdata *err);
int create_child(t_cmdtable *row, char *envp[], t_exedata *data, int *flag);
void	wait_end(t_exedata data, int pipes, t_cmdtable *row);
int	outopen(t_cmdtable *row,  int *fd, int *flag);
int	inopen(t_cmdtable *row, int *fd, char *hdpath);
//int	inopen(t_cmdtable *row, int *fd, int *flag);
void	wrtofile(int end, int filefd, char *cur, char *buf);
char	*readbuf(char *buf, int size);

#endif