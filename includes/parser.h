/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/13 00:24:51 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file we have functions used only in the parser
*/
#ifndef PARSER_H
# define PARSER_H

int		calcpipes(t_token *tkns);
int		calcargs(t_token *tkns);
int		calcins(t_token *tkns);
int		calcouts(t_token *tkns);
void	rowalloc(t_cmdtable *tbl, t_token *tkns);

//tester functions
void	printio(t_iof *files, int n);
void	printargs(char **args, int size);
#endif