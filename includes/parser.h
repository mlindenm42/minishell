/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 08:55:00 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file we have functions used only in the parser
*/
#ifndef PARSER_H
# define PARSER_H

// getpath.c
char		*getpath(char *fpath, char *envp[], t_errdata *err);

// parser_utils.c
int			calcpipes(t_tkn *tkns);
void		rowalloc(t_cmdtable *tbl, t_tkn *tkns, int pipes, t_errdata *err);

// parser.c
t_cmdtable	*parser(t_tkn *tkns, t_errdata *err);

// var_check.c
int			valid(char *str, char *envp[]);

#endif
