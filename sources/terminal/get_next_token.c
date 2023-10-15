/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:55:11 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 00:02:33 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_normal_char(char c)
{
	if ((c >= 33 && c <= 39) || (c >= 43 && c <= 58) || c == 61
		|| (c >= 63 && c <= 90) || (c >= 94 && c <= 122))
		return (1);
	return (0);
}

static void	get_next_token4(char **input)
{
	if (**input == '>' && !(*(*input + 1) == '>'))
		return (create_token(GT, (*input)++));
	if (**input == '<' && !(*(*input + 1) == '<'))
		return (create_token(LT, (*input)++));
	if (**input == '>' && (*(*input + 1)) == '>')
	{
		(*input)++;
		(*input)++;
		return (create_token(GGT, ">>"));
	}
	if (**input == '<' && (*(*input + 1)) == '<')
	{
		(*input)++;
		(*input)++;
		return (create_token(LLT, "<<"));
	}
	if (**input == '|')
	{
		(*input)++;
		return (create_token(PIPE, "|"));
	}
	add_char_to_str(input);
	return (create_tokenword(WORD));
}

static void	get_next_token3(char **input)
{
	while (is_normal_char(**input))
	{
		if (**input == '\0')
			return (create_tokenword(WORD));
		if (**input == '"')
		{
			add_char_to_str(input);
			if (dquotationcheck(input))
				return (create_token(END, "END5"));
			add_char_to_str(input);
		}
		if (**input == '\'')
		{
			add_char_to_str(input);
			if (quotationcheck(input))
				return (create_token(END, "END6"));
			add_char_to_str(input);
		}
		else
			add_char_to_str(input);
	}
	return (create_tokenword(WORD));
}

static void	get_next_token2(char **input)
{
	if (**input == '\0')
		return (create_token(END, "END1"));
	while (**input != '\0')
	{
		while (**input == ' ' || **input == '\t')
		{
			if (**input == '\0')
				return (create_token(END, "END2"));
			(*input)++;
		}
		if (**input == '\0')
			return (create_token(END, "END2"));
		if (is_normal_char(**input))
			return (get_next_token3(input));
		if (**input == '\n' || **input == '|' || **input == '('
			|| **input == ')' || **input == '<' || **input == '>')
			return (get_next_token4(input));
		(*input)++;
	}
	return (create_token(END, "END3"));
}

void	get_next_token(char **input)
{
	get_data()->slist = NULL;
	get_data()->slistend = NULL;
	get_data()->slist = (t_stringlist *)malloc(sizeof(t_stringlist));
	get_data()->slistend = get_data()->slist;
	get_data()->slistend->next = NULL;
	get_data()->slistend->character = '\0';
	return (get_next_token2(input));
}
