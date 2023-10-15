/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/15 16:36:01 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h> // printf(); FILE;
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
// # include <malloc/malloc.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h> // rl_replace_line(); rl_on_new_line();
// rl_redisplay(); readline(); rl_clear_history();
# include <readline/history.h> // add_history(input);
# include "../libs/libft/libft.h"
# include "tokens.h"
# include "structs.h"
# include "parser.h"
# include "executor.h"
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h> // signal(); SIGINT; SIGQUIT; SIGSTP; SIG_IGN;
# include <termios.h> // tcgetattr(); tcsetattr(); ECHOCTL; TCSANOW;

t_cmdtable	*parser (t_tkn *tkns, t_errdata *err);
void	expander(t_cmdtable *tbl, t_errdata *err, char *envp[]);
int	executor (t_cmdtable *tbl, char *envp[], t_errdata *err);
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop);
void	err_handler(t_errdata *err, char *str, int stop);
//void	err_handler(t_errdata *err, void *struc, void (*f)(void *), int st);
void		print_table(t_cmdtable *tbl, int size); //tester function
void		free_row(void *row);
void	free_tkns(t_tkn *tkns);
void		free_rows(void *row);
void	free_tbl(t_cmdtable **tbl);
void	free_iof(t_iof *arr, int n);
void		free_exedt(void *data);
void		free_ptr(void *p);
void		free_str(char **str);
char		**copy_arr(char **newarr, char **arr);
//void	cmderr(void *cmd);
void		cmderr(t_errdata *err, void *cmd, int stop);
void	cmderr1(t_errdata *err, void *cmd,char *env[], int stop);
void	custom_err(char *pref, const char *txt);
void		echo(char *argv[]);
void		printenv(char *env[]);
int			isbuiltin(char *cmd);
void		export(t_cmdtable *row, char *envp[]);
void		unset(t_cmdtable *row, char *envp[]);
int	cd (char *argv[], t_errdata *err);
void	pwd(void);
void	exitbuiltin(char *argv[], t_errdata *err);
void		setstatstr(t_errdata *err);
void		set_loc_env(char *envp[]);
int			arr_len(char **arr);
void		printexport(char **envp_loc);
void	execute(char *envp[], t_errdata *err);
char	*getenv1(char *var, char *envp[]);
void replace_var(char *vname, char *val, char *envp[]);
void unset_var(char *vname, char *envp[]);
char *getenvmem_end(char *envp[]);
void	movetoend(char *start, char *envp[]);
void envappend(char *str, char *envp[]);
int 	varlen(char *var);


// check.c
// void	check_arg(int argc, char *argv[]);

// init.c

// error.c
void	error(char *reason);
// void	free_all(void);

// lexer.c
void	lexer(char *input);

// main.c
t_data	*get_data(void);

// terminal.c
void	terminal(char *envp[], t_errdata *err);
void	handle_ctrl_c(int signal);
void	handle_ctrl_d(t_errdata *err);
void	handle_ctrl_backslash(int signal);

// utils.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strtrim(char const *s1, char const *set);

//utils_ft_split.c
char	**ft_split(char const *s, char c);

#endif
