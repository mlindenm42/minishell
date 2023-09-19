/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:03:19 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/19 17:18:28 by mlindenm         ###   ########.fr       */
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

// t_tkn		*lexer(); //dummy function
t_cmdtable	*parser (t_tkn *tkns, char *envp[], t_errdata *err);
void	    expander(t_cmdtable *tbl, t_errdata *err);
int	        executor (t_cmdtable *tbl, char *envp[], t_errdata *err);
void	    errfree(t_errdata *err, void *struc, void (*del)(void *), int stop);
void	    err_handler(t_errdata *err, char *str, int stop);
//void	err_handler(t_errdata *err, void *struc, void (*f)(void *), int st);
void	    print_table(t_cmdtable *tbl, int size); //tester function
void	    free_row(void *row);
void	    free_rows(void *row);
void	    free_exedt(void *data);
void	    free_ptr(void *p);
//void	cmderr(void *cmd);
void	    cmderr(t_errdata *err, void *cmd, int stop);
void	    echo(char *argv[]);
int		    isbuiltin(char *cmd);
void	    setstatstr(t_errdata *err);
//void	cmderr(void *cmd);
//void	addtext(void *fpath, t_errdata *err);

// check.c
// void	check_arg(int argc, char *argv[]);

// init.c

// error.c
void	error(char *reason);
// void	free_all(void);

// lexer.c
t_tkn	lexer(char *input);

// main.c
t_data	*get_data(void);

// terminal.c
void	terminal(void);

// utils.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strtrim(char const *s1, char const *set);

//utils_ft_split.c
char	**ft_split(char const *s, char c);

#endif
