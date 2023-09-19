/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:32:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/29 21:55:02 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h> // printf();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

t_token	*create_token(int type, const char *val)
{
	t_token	*token;

	token = NULL;
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		error("malloc");
	token->type = type;
	token->val = strdup(val);
	return (token);
}

void	free_token(t_token *token)
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

int	token_counter(char *input)
{
	int	i;

	if (*input == '\0')
		return (1);
	i = 1;
	while (*input != '\0')
	{
		while (*input == ' ' || *input == '\t')
		{
			if (*input == '\0')
				return (i);
			input++;
		}
		if (is_normal_char(*input))
		{
			i++;
			while (is_normal_char(*input))
			{
				if (*input == '\0')
					return (i);
				if (*input == '"')
				{
					input++;
					while (*input != '"')
					{
						if (*input == '\0')
							error("wrong syntax!\n");
						input++;
					}
				}
				if (*input == '\'')
				{
					input++;
					while (*input != '\'')
					{
						if (*input == '\0')
							error("wrong syntax!\n");
						input++;
					}
				}
				input++;
			}
		}
		if (*input == '\n' || *input == '|' || *input == '&' || *input == ';' || *input == '(' || *input == ')' || *input == '<' || *input == '>')
			i++;
		input++;
	}
	return (i);
}

int	char_counter(char *input)
{
	char	c;

	c = *input;
	c++;
	return (100);
}

t_token	*get_next_token(char **input)
{
	if (**input == '\0')
		return (create_token(END, "END"));
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
				(*input)++;
			}
			return (create_token(WORD, "B"));
		}
		if (**input == '\n' || **input == '|' || **input == '&' || **input == ';' || **input == '(' || **input == ')' || **input == '<' || **input == '>')
		{
			(*input)++;
			return (create_token(WORD, "OP"));
		}
		(*input)++;
	}
	return (create_token(END, "C"));
}

void	lexer(char *input)
{
	int		i;
	int		counter;

	printf("Input: %s\n", input);
	// input = ft_strtrim(input, " ");
	// input = ft_strtrim(input, "\t");
	counter = token_counter(input);
	printf("Tokens: %d\n", counter);
	get_data()->tokens = (t_token **) malloc(counter * sizeof(t_token *));
	i = 0;
	while (i < counter)
	{
		get_data()->tokens[i] = get_next_token(&input);
		// if (get_data()->tokens[i]->type == END)
		// 	break ;
		printf("Token type: %d, Value: %s\n",
			get_data()->tokens[i]->type, get_data()->tokens[i]->val);
		i++;
	}
}
