/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:20:40 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/15 01:05:38 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h> // printf();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void	free_stringlist(t_stringlist *string)
{
	t_stringlist	*actual;
	t_stringlist	*copy;

	actual = string;
	while (actual->next != NULL)
	{
		copy = actual;
		actual = actual->next;
		free(copy);
	}
	free(actual);
}

t_tkn	*create_token(int type, const char *val)
{
	t_tkn	*token;

	token = NULL;
	token = (t_tkn *)malloc(sizeof(t_tkn));
	if (token == NULL)
		error("token malloc failure");
	token->type = type;
	token->val = ft_strdup(val);
	return (token);
}

int	get_string_length(t_stringlist *string)
{
	t_stringlist	*actual;
	int				counter;

	actual = string;
	counter = 1;
	while (actual->next != NULL)
	{
		counter++;
		actual = actual->next;
	}
	return (counter);
}

t_tkn	*create_tokenword(int type, t_stringlist *string)
{
	t_tkn			*token;
	t_stringlist	*actual;
	int				i;

	token = NULL;
	token = (t_tkn *)malloc(sizeof(t_tkn));
	if (token == NULL)
		error("token malloc failure");
	token->type = type;
	actual = string;
	token->val = (char *)malloc(get_string_length(string) * sizeof(char));
	i = 0;
	while (actual->next != NULL)
	{
		token->val[i++] = actual->character;
		actual = actual->next;
	}
	token->val[i] = '\0';
	free_stringlist(string);
	return (token);
}

int	is_normal_char(char c)
{
	if ((c >= 33 && c <= 39) || (c >= 43 && c <= 58) || c == 61 || (c >= 63 && c <= 90) || (c >= 94 && c <= 122))
		return (1);
	return (0);
}

void	add_char_to_str(t_stringlist **string, char **c)
{
	(*string)->character = **c;
	(*string)->next = (t_stringlist *)malloc(sizeof(t_stringlist));
	(*string) = (*string)->next;
	(*string)->next = NULL;
	(*string)->character = '\0';
	(*c)++;
}
// void	get_next_token5(char **input, t_stringlist *actual)
// {
// 			add_char_to_str(&actual, input);
// 			while (**input != '"')
// 			{
// 				if (**input == '\0')
// 					error("wrong syntax!\n");
// 				add_char_to_str(&actual, input);
// 			}
// 			add_char_to_str(&actual, input);
// }

t_tkn	*get_next_token3(char **input, t_stringlist *begin, t_stringlist *actual)
{
	while (is_normal_char(**input))
	{
		if (**input == '\0')
			return (create_tokenword(WORD, begin));
		if (**input == '"')
		{
			// get_next_token5(input, actual);
			add_char_to_str(&actual, input);
			while (**input != '"')
			{
				if (**input == '\0')
					error("wrong syntax!\n");
				add_char_to_str(&actual, input);
			}
			add_char_to_str(&actual, input);
		}
		if (**input == '\'')
		{
			add_char_to_str(&actual, input);
			while (**input != '\'')
			{
				if (**input == '\0')
					error("wrong syntax!\n");
				add_char_to_str(&actual, input);
			}
			add_char_to_str(&actual, input);
		}
		else
			add_char_to_str(&actual, input);
	}
	return (create_tokenword(WORD, begin));
}

t_tkn	*get_next_token4(char **input, t_stringlist *begin, t_stringlist *actual)
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
	add_char_to_str(&actual, input);
	return (create_tokenword(WORD, begin));
}

t_tkn	*get_next_token2(char **input, t_stringlist *begin, t_stringlist *actual)
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
		if (is_normal_char(**input))
			return (get_next_token3(input, begin, actual));
		if (**input == '\n' || **input == '|' || **input == '(' || **input == ')' || **input == '<' || **input == '>')
			return (get_next_token4(input, begin, actual));
		(*input)++;
	}
	return (create_token(END, "END3"));
}

t_tkn	*get_next_token(char **input)
{
	t_stringlist	*begin;
	t_stringlist	*actual;

	begin = NULL;
	begin = (t_stringlist *)malloc(sizeof(t_stringlist));
	actual = begin;
	actual->next = NULL;
	actual->character = '\0';
	return (get_next_token2(input, begin, actual));
}

void	tokenlist_to_array(void)
{
	int			counter;
	t_tokenlist	*actual;
	int			i;

	counter = 0;
	actual = get_data()->tlist;
	while (actual != NULL)
	{
		counter++;
		actual = actual->next;
	}
	get_data()->tokens = (t_tkn *) malloc(counter * sizeof(t_tkn));
	i = 0;
	actual = get_data()->tlist;
	while (i < counter)
	{
		get_data()->tokens[i].type = actual->token.type;
		get_data()->tokens[i].val = actual->token.val;
		actual = actual->next;
		i++;
	}
}

void	free_tokenlist(void)
{
	t_tokenlist	*actual;
	t_tokenlist	*copy;

	actual = get_data()->tlist;
	while (actual != NULL && actual->token.type != END)
	{
		copy = actual;
		actual = actual->next;
		free(copy);
	}
	free(actual);
	get_data()->tlist = NULL;
	get_data()->tlistend = NULL;
}
void	print_tokens(void)
{
	int i = 0;
	while (get_data()->tokens[i].type != END)
	{
		printf("Token type: %d, Value: %s\n", get_data()->tokens[i].type, get_data()->tokens[i].val);
		i++;
	}
	printf("Token type: %d, Value: %s\n", get_data()->tokens[i].type, get_data()->tokens[i].val);
}

void	lexer(char *input)
{
	t_tokenlist	*copy;

	get_data()->tlist = NULL;
	get_data()->tlist = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	get_data()->tlistend = get_data()->tlist;
	get_data()->tlistend->next = NULL;
	get_data()->tlistend->token = *get_next_token(&input);
	while (*input != '\0')
	{
		get_data()->tlistend->next = (t_tokenlist *)malloc(sizeof(t_tokenlist));
		get_data()->tlistend = get_data()->tlistend->next;
		get_data()->tlistend->next = NULL;
		get_data()->tlistend->token = *get_next_token(&input);
	}
	if (get_data()->tlistend->token.type != END)
	{
		get_data()->tlistend->next = (t_tokenlist *)malloc(sizeof(t_tokenlist));
		get_data()->tlistend = get_data()->tlistend->next;
		get_data()->tlistend->next = NULL;
		get_data()->tlistend->token = *create_token(END, "END4");
	}
	tokenlist_to_array();
	free_tokenlist();
	// print_tokens();
}
