/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/12 23:51:42 by mrubina          ###   ########.fr       */
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
int	executor (t_cmdtable *tbl, char *envp[], t_errdata *err);
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop);
void	err_handler(t_errdata *err, char *str, int stop);
//void	err_handler(t_errdata *err, void *struc, void (*f)(void *), int st);
void	print_table(t_cmdtable *tbl, int size); //tester function
void	free_row(void *row);
void	free_rows(void *row);
void	free_exedt(void *data);
void	free_ptr(void *p);
//void	cmderr(void *cmd);
void	cmderr(t_errdata *err, void *cmd, int stop);
//void	cmderr(void *cmd);
//void	addtext(void *fpath, t_errdata *err);
#endif