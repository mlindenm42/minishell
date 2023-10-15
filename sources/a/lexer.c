/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:20:40 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/15 00:22:24 by mrubina          ###   ########.fr       */
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

void	free_tokenlist(t_tokenlist *tokenlist)
{
	t_tokenlist	*actual;
	t_tokenlist	*copy;

	actual = tokenlist;
	while (actual->next != NULL)
	{
		copy = actual;
		actual = actual->next;
		free(copy);
	}
	free(actual);
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

t_tkn	*create_tokenword(int type, t_stringlist *string)
{
	t_tkn			*token;
	t_stringlist	*actual;
	int				counter;
	int				i;

	token = NULL;
	token = (t_tkn *)malloc(sizeof(t_tkn));
	if (token == NULL)
		error("malloc");
	token->type = type;
	actual = string;
	counter = 0;
	while (actual->next != NULL)
	{
		counter++;
		actual = actual->next;
	}
	actual = string;
	token->val = (char *)malloc(counter * sizeof(char));
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
				return (create_token(END, "END2"));
			(*input)++;
		}
		if (is_normal_char(**input))
		{
			while (is_normal_char(**input))
			{
				if (**input == '\0')
					return (create_tokenword(WORD, begin));
				if (**input == '"')
				{
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
		if (**input == '\n' || **input == '|' || **input == '(' || **input == ')' || **input == '<' || **input == '>')
		{
			if (**input == '>' && !(*(*input + 1) == '>'))
			{
				(*input)++;
				return (create_token(GT, ">"));
			}
			if (**input == '<' && !(*(*input + 1) == '<'))
			{
				(*input)++;
				return (create_token(LT, "<"));
			}
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
		(*input)++;
	}
	return (create_token(END, "END3"));
}

void	tokenlist_to_array(t_tokenlist *token_list)
{
	int			counter;
	t_tokenlist	*actual;
	int			i;

	counter = 0;
	actual = token_list;
	while (actual != NULL)
	{
		counter++;
		actual = actual->next;
	}
	get_data()->tokens = (t_tkn *) malloc(counter * sizeof(t_tkn));
	i = 0;
	actual = token_list;
	while (i < counter)
	{
		get_data()->tokens[i] = actual->token;
		actual = actual->next;
		i++;
	}
}

void	lexer(char *input)
{
	t_tokenlist	*begin;
	t_tokenlist	*actual;

	begin = NULL;
	begin = (t_tokenlist *)malloc(sizeof(t_tokenlist));
	actual = begin;
	actual->next = NULL;
	actual->token = *get_next_token(&input);
	while (*input != '\0')
	{
		actual->next = (t_tokenlist *)malloc(sizeof(t_tokenlist));
		actual = actual->next;
		actual->next = NULL;
		actual->token = *get_next_token(&input);
	}
	if (actual->token.type != END)
	{
		actual->next = (t_tokenlist *)malloc(sizeof(t_tokenlist));
		actual = actual->next;
		actual->next = NULL;
		actual->token = *create_token(END, "END4");
	}
	tokenlist_to_array(begin);
	free_tokenlist(begin);
	// dprintf(2, "token val %s\n", get_data()->tokens[0].val);
	// free(get_data()->tokens[0].val);
	//get_data()->tokens[i].val;
 	// int i = 0;
	// while (get_data()->tokens[i].type != END)
	// {
	// 	printf("Token type: %d, Value: %s\n", get_data()->tokens[i].type, get_data()->tokens[i].val);
	// 	i++;
	// }
	// printf("Token type: %d, Value: %s\n", get_data()->tokens[i].type, get_data()->tokens[i].val);
}
