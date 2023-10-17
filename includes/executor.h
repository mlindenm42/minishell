/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 20:03:11 by mrubina          ###   ########.fr       */
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

// exe_utils.c
void	redir_close(int fd, int stdfd, t_errdata *err);
int		create_pipe(t_exedata *data, t_errdata *err);
int		ft_strcmp(const char *s1, const char *s2);
void	exe_builtin(t_cmdtable *row, char *envp[], t_errdata *err, int id);
int		create_child(t_cmdtable *row, char *envp[], t_errdata *err);

// executor.c
int		executor(t_cmdtable *tbl, char *envp[], t_errdata *err);

// expander.c
void	expander(t_cmdtable *tbl, t_errdata *err);

// heredoc.c
int		heredoc(t_cmdtable *tbl, t_exedata *data, t_errdata *err);

// ins_outs.c
void	inopen(t_cmdtable *row, int *fd, char *hdpath, t_errdata *err);
int		outopen(t_cmdtable *row, int *fd, int stop, t_errdata *err);
void	midouts(t_cmdtable *row, t_exedata *data, t_errdata *err);
void	setnextin(t_cmdtable *row, t_exedata *data, t_errdata *err, int i);

// quote_utils.c
int		replace_q(char **word, char *next, t_errdata *err);

// vars.c
char	*skip_var(char *start);
char	*strjoin3(char *str1, char *str2, char *str3, t_errdata *err);
void	varscan(char **word, char *env[], t_errdata *err);
void	varscannq(char **word, char *envp[], t_errdata *err);

#endif
