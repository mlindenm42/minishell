/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/17 21:10:59 by mrubina          ###   ########.fr       */
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

//error
# define ERR 3

//constants showing what to do after error stop/continue/go to the next pipeline
//
# define STP 5
# define CNT 6
# define NXT 7

int		heredoc	(t_cmdtable *tbl, t_exedata *data);
void	redir_close(int fd, int stdfd,  t_errdata *err);
int		create_pipe(t_exedata *data, t_errdata *err);
int 	create_child(t_cmdtable *row, char *envp[], t_exedata *data);
int		outopen(t_cmdtable *row,  int *fd, int stop);
void	inopen(t_cmdtable *row, int *fd, char *hdpath);
void	wrtofile(int end, int filefd, char *cur, char *buf);
char	*readbuf(char *buf, int size);
void	midouts(t_cmdtable *row, t_exedata *data);
void	setnextin(t_cmdtable *row, t_exedata *data, int i);
int		ft_strcmp(const char *s1, const char *s2);
#endif