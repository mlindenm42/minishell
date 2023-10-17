/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:55:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 09:00:40 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

// free_terminal.c
void		free_stringlist(void);
void		free_tokenlist(void);
void		free_tokens(void);

// get_next_token.c
void		get_next_token(char **input, t_errdata *err);

// lexer.c
void		add_char_to_str(char **c, t_errdata *err);
int			dquotationcheck(char **input, t_errdata *err);
int			quotationcheck(char **input, t_errdata *err);
void		lexer(char *input, t_errdata *err);

// terminal.c
void		handle_ctrl_c(int signal);
void		handle_ctrl_backslash(int signal);
void		terminal(char *envp[], t_errdata *err);

// token.c
void		create_tokenword(int type, t_errdata *err);
void		create_token(int type, const char *val, t_errdata *err);
void		tokenlist_to_array(t_errdata *err);

#endif
