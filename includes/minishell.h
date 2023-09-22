/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/22 23:02:31 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <malloc/malloc.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"
# include "tokens.h"
# include "structs.h"
# include "parser.h"
# include "executor.h"

t_tkn		*lexer(); //dummy function
t_cmdtable	*parser (t_tkn *tkns, char *envp[], t_errdata *err);
void	expander(t_cmdtable *tbl, t_errdata *err);
int	executor (t_cmdtable *tbl, char *envp[], t_errdata *err);
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop);
void	err_handler(t_errdata *err, char *str, int stop);
//void	err_handler(t_errdata *err, void *struc, void (*f)(void *), int st);
void	print_table(t_cmdtable *tbl, int size); //tester function
void	free_row(void *row);
void	free_rows(void *row);
void	free_exedt(void *data);
void	free_ptr(void *p);
void	free_str(char *str);
char	**copy_arr(char **newarr, char **arr);
//void	cmderr(void *cmd);
void	cmderr(t_errdata *err, void *cmd, int stop);
void	echo(char *argv[]);
void	printenv(char *env[]);
int		isbuiltin(char *cmd);
void export(char **envp_loc, t_cmdtable *row);
void	setstatstr(t_errdata *err);
void	set_loc_env(char *envp[], t_errdata *err);
int		arr_len(char **arr);
char	**expand_loc_env(char **envp_loc, int nvar);//move to execotor
//void	cmderr(void *cmd);
//void	addtext(void *fpath, t_errdata *err);
#endif