/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 20:51:34 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file we have functions used only in the parser
*/
#ifndef PARSER_H
# define PARSER_H

int		calcpipes(t_tkn *tkns);
int		calcargs(t_tkn *tkns, char *envp[]);
int		calcins(t_tkn *tkns);
int		calcouts(t_tkn *tkns);
void	rowalloc(t_cmdtable *tbl, t_tkn *tkns, int pipes, t_errdata *err);
char	*getpath(char *fpath, char *envp[], t_errdata *err);
int		varvalid(char *str, char *envp[]);
void	free_arr(char **arr);

//tester functions
void	printio(t_iof *files, int n);
void	printargs(char **args, int size);
#endif