/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:20:40 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/21 17:21:00 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h> // printf();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_tokenlist
{
	struct s_tokenlist	*next;
	t_tkn				token;
}	t_tokenlist;

typedef struct s_stringlist
{
	struct s_stringlist	*next;
	char				character;
}	t_stringlist;

t_tkn	*create_token(int type, const char *val)
{
	t_tkn	*token;

	token = NULL;
	token = (t_tkn *)malloc(sizeof(t_tkn));
	if (token == NULL)
		error("malloc");
	token->type = type;
	token->val = ft_strdup(val);
	return (token);
}

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

t_tkn	*create_tokenn(int type, t_stringlist *string)
{
	t_tkn	*token;
	t_stringlist	*actual;
	int		counter;
	int		i;

	token = NULL;
	token = (t_tkn *)malloc(sizeof(t_tkn));
	if (token == NULL)
		error("malloc");
	token->type = type;
	actual = string;
	counter = 1;
	while (actual->next != NULL)
	{
		counter++;
		actual = actual->next;
	}
	actual = string;
	token->val = (char *)malloc((counter + 1) * sizeof(char));
	i = 0;
	while (i < counter)
	{
		token->val[i++] = actual->character;
		actual = actual->next;
	}
	token->val[i] = '\0';
	free_stringlist(string);
	return (token);
}

void	free_token(t_tkn *token)
{
	free(token->val);
	free(token);
}

int	is_normal_char(char c)
{
	if (c == '!' || (c >= '"' && c <= '\'') || (c >= '+' && c <= '.') || (c >= '/' && c <= ':') || c == '=' || (c >= '?' && c <= 'Z') || (c >= '^' && c <= 'z'))
		return (1);
	return (0);
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
	if (**input == '\0')
		return (create_token(END, "END1"));
	while (**input != '\0')
	{
		while (**input == ' ' || **input == '\t')
		{
			if (**input == '\0')
				return &(*get_next_token(input));
			(*input)++;
		}
		if (is_normal_char(**input))
		{
			while (is_normal_char(**input))
			{
				if (**input == '\0')
					return (create_token(WORD, "A"));
				if (**input == '"')
				{
					(*input)++;
					while (**input != '"')
					{
						if (**input == '\0')
							error("wrong syntax!\n");
						(*input)++;
					}
				}
				if (**input == '\'')
				{
					(*input)++;
					while (**input != '\'')
					{
						if (**input == '\0')
							error("wrong syntax!\n");
						(*input)++;
					}
				}
				actual->character = **input;
				actual->next = (t_stringlist *)malloc(sizeof(t_stringlist));
				actual = actual->next;
				actual->next = NULL;
				actual->character = '\0';
				(*input)++;
			}
			return (create_tokenn(WORD, begin));
		}
		if (**input == '\n' || **input == '|' || **input == '&' || **input == ';' || **input == '(' || **input == ')' || **input == '<' || **input == '>')
		{
			(*input)++;
			return (create_token(WORD, "OP"));
		}
		(*input)++;
	}
	// printf("TEST: %s\n", *input);
	return &(*get_next_token(input));
}

void	lexer(char *input)
{
	int		i;
	t_tokenlist	*begin;
	t_tokenlist	*actual;

	// printf("Input: %s\n", input);
	begin = NULL;
	begin = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	actual = begin;
	actual->next = NULL;
	actual->token = *get_next_token(&input);
	// printf("Token type: %d, Value: %s\n", actual->token.type, actual->token.val);
	// input = ft_strtrim(input, " ");
	// input = ft_strtrim(input, "\t");
	i = 0;
	while (*input != '\0')
	{
		// printf("REST Input: %s\n", input);
		actual->next = (t_tokenlist *)malloc(sizeof(t_tokenlist));
		actual = actual->next;
		actual->next = NULL;
		actual->token = *get_next_token(&input);
		// printf("Token type: %d, Value: %s\n", actual->token.type, actual->token.val);
		i++;
	}
	// printf("\n");
	actual = begin;
	while (actual->next != NULL)
	{
		printf("Token type: %d, Value: %s\n", actual->token.type, actual->token.val);
		actual = actual->next;
	}
	printf("Token type: %d, Value: %s\n", actual->token.type, actual->token.val);
	return ;
}
