/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:03:19 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/13 23:37:56 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokens.h"
# include "structs.h"
# include "parser.h"

# include <stdlib.h> // size_t;

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
void	terminal(void);

// utils.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t n);

//utils_ft_split.c
char	**ft_split(char const *s, char c);

#endif
