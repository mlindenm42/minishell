/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:20:40 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 01:09:07 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_char_to_str(char **c, t_errdata *err)
{
	get_data()->slistend->character = **c;
	(get_data()->slistend->next
			= create_pile(&err->gc, sizeof(t_stringlist), 1));
	get_data()->slistend = get_data()->slistend->next;
	get_data()->slistend->next = NULL;
	get_data()->slistend->character = '\0';
	(*c)++;
}

int	dquotationcheck(char **input, t_errdata *err)
{
	while (**input != '"')
	{
		if (**input == '\0')
		{
			free_stringlist();
			free_tokenlist();
			free_tokens();
			if (get_data()->tokens != NULL)
			{
				free(get_data()->tokens);
				get_data()->tokens = NULL;
			}
			write(2, "quotation not closed\n", 21);
			get_data()->input[0] = '\0';
			get_data()->tlist = NULL;
			get_data()->tlist = create_pile(&err->gc, sizeof(t_tokenlist), 1);
			get_data()->tlistend = get_data()->tlist;
			get_data()->tlistend->next = NULL;
			return (1);
		}
		add_char_to_str(input, err);
	}
	return (0);
}

int	quotationcheck(char **input, t_errdata *err)
{
	while (**input != '\'')
	{
		if (**input == '\0')
		{
			free_stringlist();
			free_tokenlist();
			free_tokens();
			if (get_data()->tokens != NULL)
			{
				free(get_data()->tokens);
				get_data()->tokens = NULL;
			}
			write(2, "quotation not closed\n", 21);
			get_data()->input[0] = '\0';
			get_data()->tlist = NULL;
			get_data()->tlist = create_pile(&err->gc, sizeof(t_tokenlist), 1);
			get_data()->tlistend = get_data()->tlist;
			get_data()->tlistend->next = NULL;
			return (1);
		}
		add_char_to_str(input, err);
	}
	return (0);
}

void	pipecheck(t_errdata *err)
{
	if (get_data()->tokens[get_data()->tokenslength - 2].type == PIPE)
	{
		write(2, "pipe not closed\n", 16);
		get_data()->tlist = NULL;
		get_data()->tlist = create_pile(&err->gc, sizeof(t_tokenlist), 1);
		get_data()->tlistend = get_data()->tlist;
		get_data()->tlistend->token.type = NOTOKEN;
		get_data()->tlistend->next = NULL;
		create_token(END, "END7", err);
		tokenlist_to_array(err);
	}
}

void	lexer(char *input, t_errdata *err)
{
	get_data()->tlist = NULL;
	get_data()->tlist = create_pile(&err->gc, sizeof(t_tokenlist), 1);
	get_data()->tlistend = get_data()->tlist;
	get_data()->tlistend->token.type = NOTOKEN;
	get_data()->tlistend->next = NULL;
	get_next_token(&input, err);
	while (*input != '\0')
	{
		(get_data()->tlistend->next
				= create_pile(&err->gc, sizeof(t_tokenlist), 1));
		get_data()->tlistend = get_data()->tlistend->next;
		get_data()->tlistend->next = NULL;
		get_next_token(&input, err);
	}
	if (get_data()->tlistend->token.type != END)
	{
		(get_data()->tlistend->next
				= create_pile(&err->gc, sizeof(t_tokenlist), 1));
		get_data()->tlistend = get_data()->tlistend->next;
		get_data()->tlistend->next = NULL;
		create_token(END, "END4", err);
	}
	tokenlist_to_array(err);
	pipecheck(err);
}
