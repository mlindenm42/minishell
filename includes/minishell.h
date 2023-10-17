/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 02:12:10 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 10:41:51 by mlindenm         ###   ########.fr       */
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
// # include <malloc/malloc.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"
# include "builtins.h"
# include "executor.h"
# include "parser.h"
# include "structs.h"
# include "terminal.h"
# include "tokens.h"
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>

// array_utils.c
void	free_arr(char **arr);
char	**copy_arr(char **newarr, char **arr);
int		arr_len(char **arr);

// err_handler.c
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop);
void	custom_err(char *pref, const char *txt, t_errdata *err);
void	err_handler(t_errdata *err, char *str, int stop);
void	cmderr(t_errdata *err, void *cmd, int stop);
void	cmderr1(t_errdata *err, void *cmd, char *env[], int stop);

// execute.c
void	execute(char *envp[], t_errdata *err);

// free_data.c
void	*create_elem(t_free *ree, int i, int j);
void	free_data(t_free *ree, t_free_elem *elem);

// main.c
t_data	*get_data(void);

#endif
