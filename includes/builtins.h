/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:55:59 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 10:40:43 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// builtins_utils.c
int		isbuiltin(char *cmd);
int		env_change(char *cmd, int nrows);
void	exitbuiltin(char *argv[], t_errdata *err);

// cd.c
void	pwd(void);
int		cd(char *argv[], char *envp[], t_errdata *err);

// echo.c
void	echo(char *argv[]);

// env_utils.c
void	replace_var(char *v, char *val, char *e[]);
void	unset_var(char *vname, char *envp[]);

// env.c
void	printenv(char *envp[]);
char	*getenvmem_end(char *envp[]);
void	shiftenv(char *var, char *envp[], int shift, char *end);
char	*getenv1(char *var, char *envp[]);
void	set_loc_env(char *envp[], t_errdata *err);

// export_utils.c
void	arr_sort(char **arr, int n);

// export.c
void	envappend(char *str, char *envp[]);
void	export(t_cmdtable *row, char *envp[]);

//unset.c
void	unset(t_cmdtable *row, char *envp[]);

#endif
