/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/20 13:57:58 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file we have functions used only in the parser
*/
#ifndef PARSER_H
# define PARSER_H

int		calcpipes(t_tkn *tkns);
int		calcargs(t_tkn *tkns);
int		calcins(t_tkn *tkns);
int		calcouts(t_tkn *tkns);
void	rowalloc(t_cmdtable *tbl, t_tkn *tkns, int pipes, t_errdata *err);
char	*getpath(char *fpath, char *envp[]);
int		varvalid(char *str);

//tester functions
void	printio(t_iof *files, int n);
void	printargs(char **args, int size);
#endif