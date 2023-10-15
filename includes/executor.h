/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/14 18:18:11 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file we have functions used only in the executor
*/
#ifndef EXECUTOR_H
# define EXECUTOR_H

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

int		heredoc(t_cmdtable *tbl, t_exedata *data, t_errdata *err);
void	redir_close(int fd, int stdfd, t_errdata *err);
int		create_pipe(t_exedata *data, t_errdata *err);
int		create_child(t_cmdtable *row, char *envp[], t_errdata *err);
int		outopen(t_cmdtable *row, int *fd, int stop, t_errdata *err);
void	inopen(t_cmdtable *row, int *fd, char *hdpath, t_errdata *err);
void	wrtofile(int end, int filefd, char *cur, char *buf);
char	*readbuf(char *buf, int size);
void	midouts(t_cmdtable *row, t_exedata *data, t_errdata *err);
void	setnextin(t_cmdtable *row, t_exedata *data, t_errdata *err, int i);
int		ft_strcmp(const char *s1, const char *s2);
char	*varsubst(char **str, char *start, char *exit_stat, char *env[]);
void	varscan(char **word, char *exit_stat, char *env[]);
void	expand_word(char **word, char *exit_stat, char *env[]);
char	*skip_var(char *start);
void	exe_builtin(t_cmdtable *row, char *envp[], t_errdata *err, int id);
void	arr_sort(char **arr, int n);
int		env_change(char *cmd, int nrows);
#endif