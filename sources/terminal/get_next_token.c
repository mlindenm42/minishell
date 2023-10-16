/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:55:11 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 22:30:23 by mlindenm         ###   ########.fr       */
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

static void	get_next_token4(char **input, t_errdata *err)
{
	if (**input == '>' && !(*(*input + 1) == '>'))
		return (create_token(GT, (*input)++, err));
	if (**input == '<' && !(*(*input + 1) == '<'))
		return (create_token(LT, (*input)++, err));
	if (**input == '>' && (*(*input + 1)) == '>')
	{
		(*input)++;
		(*input)++;
		return (create_token(GGT, ">>", err));
	}
	if (**input == '<' && (*(*input + 1)) == '<')
	{
		(*input)++;
		(*input)++;
		return (create_token(LLT, "<<", err));
	}
	if (**input == '|')
	{
		(*input)++;
		return (create_token(PIPE, "|", err));
	}
	add_char_to_str(input, err);
	return (create_tokenword(WORD, err));
}

static void	get_next_token3(char **input, t_errdata *err)
{
	while (is_normal_char(**input))
	{
		if (**input == '\0')
			return (create_tokenword(WORD, err));
		if (**input == '"')
		{
			add_char_to_str(input, err);
			if (dquotationcheck(input, err))
				return (create_token(END, "END5", err));
			add_char_to_str(input, err);
		}
		if (**input == '\'')
		{
			add_char_to_str(input, err);
			if (quotationcheck(input, err))
				return (create_token(END, "END6", err));
			add_char_to_str(input, err);
		}
		else
			add_char_to_str(input, err);
	}
	return (create_tokenword(WORD, err));
}

static void	get_next_token2(char **input, t_errdata *err)
{
	if (**input == '\0')
		return (create_token(END, "END1", err));
	while (**input != '\0')
	{
		while (**input == ' ' || **input == '\t')
		{
			if (**input == '\0')
				return (create_token(END, "END2", err));
			(*input)++;
		}
		if (**input == '\0')
			return (create_token(END, "END2", err));
		if (is_normal_char(**input))
			return (get_next_token3(input, err));
		if (**input == '\n' || **input == '|' || **input == '('
			|| **input == ')' || **input == '<' || **input == '>')
			return (get_next_token4(input, err));
		(*input)++;
	}
	return (create_token(END, "END3", err));
}

void	get_next_token(char **input, t_errdata *err)
{
	get_data()->slist = NULL;
	get_data()->slistend = NULL;
	get_data()->slist = create_pile(&err->gc, sizeof(t_stringlist), 1);
	get_data()->slistend = get_data()->slist;
	get_data()->slistend->next = NULL;
	get_data()->slistend->character = '\0';
	return (get_next_token2(input, err));
}
