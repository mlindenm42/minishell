/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/28 23:35:26 by mrubina          ###   ########.fr       */
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
void	rowalloc(t_cmdtable *tbl, t_tkn *tkns, int pipes, char *envp[]);
char	*getpath(char *fpath, char *envp[]);
int		varvalid(char *str, char *envp[]);
void	free_arr(char **arr);

//tester functions
void	printio(t_iof *files, int n);
void	printargs(char **args, int size);
#endif