/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/23 16:51:21 by mrubina          ###   ########.fr       */
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
void	executor (t_cmdtable *tbl, char *envp[], t_errdata *err);
void	err_handler(t_errdata *err, void *struc, void (*del)(void *), int st);
void	print_table(t_cmdtable *tbl, int size); //tester function
void	free_row(void *row);
void	free_rows(void *row);
#endif