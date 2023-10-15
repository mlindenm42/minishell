/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:20:40 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 00:14:56 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_char_to_str(char **c)
{
	get_data()->slistend->character = **c;
	get_data()->slistend->next = (t_stringlist *)malloc(sizeof(t_stringlist));
	get_data()->slistend = get_data()->slistend->next;
	get_data()->slistend->next = NULL;
	get_data()->slistend->character = '\0';
	(*c)++;
}

int	dquotationcheck(char **input)
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
			get_data()->tlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
			get_data()->tlistend = get_data()->tlist;
			get_data()->tlistend->next = NULL;
			return (1);
		}
		add_char_to_str(input);
	}
	return (0);
}

int	quotationcheck(char **input)
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
			get_data()->tlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
			get_data()->tlistend = get_data()->tlist;
			get_data()->tlistend->next = NULL;
			return (1);
		}
		add_char_to_str(input);
	}
	return (0);
}

void	lexer(char *input)
{
	get_data()->tlist = NULL;
	get_data()->tlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	get_data()->tlistend = get_data()->tlist;
	get_data()->tlistend->token.type = NOTOKEN;
	get_data()->tlistend->next = NULL;
	get_next_token(&input);
	while (*input != '\0')
	{
		get_data()->tlistend->next = (t_tokenlist *)malloc(sizeof(t_tokenlist));
		get_data()->tlistend = get_data()->tlistend->next;
		get_data()->tlistend->next = NULL;
		get_next_token(&input);
	}
	if (get_data()->tlistend->token.type != END)
	{
		get_data()->tlistend->next = (t_tokenlist *)malloc(sizeof(t_tokenlist));
		get_data()->tlistend = get_data()->tlistend->next;
		get_data()->tlistend->next = NULL;
		create_token(END, "END4");
	}
	tokenlist_to_array();
	free_stringlist();
	free_tokenlist();
}
