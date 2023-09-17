/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:32:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/18 00:22:01 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h> // printf();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

t_tkn	*create_token(int type, const char *val)
{
	t_tkn	*token;

	token = NULL;
	token = (t_tkn *)malloc(sizeof(t_tkn));
	if (token == NULL)
		error("malloc");
	token->type = type;
	token->val = strdup(val);
	return (token);
}

void	free_token(t_tkn *token)
{
	free(token->val);
	free(token);
}

t_tkn	*get_next_tkn(char **input)
{
	char	val[256];
	int		i;

	if (**input == '\0')
		return (create_token(END, ""));
	if (**input == '|')
	{
		(*input)++;
		return (create_token(PIPE, "|"));
	}
	else if (**input == '<')
	{
		(*input)++;
		return (create_token(LT, "<"));
	}
	else if (**input == '>')
	{
		(*input)++;
		return (create_token(GT, ">"));
	}
	i = 0;
	while (**input != '\0' && **input != ' ' && **input != '\t'
		&& **input != '|' && **input != '<' && **input != '>')
	{
		val[i++] = **input;
		(*input)++;
	}
	val[i] = '\0';
	if (strcmp(val, "echo") == 0 || strcmp(val, "cd") == 0
		|| strcmp(val, "pwd") == 0 || strcmp(val, "export") == 0
		|| strcmp(val, "unset") == 0 || strcmp(val, "env") == 0
		|| strcmp(val, "exit") == 0)
		return (create_token(CMD, val));
	else
		return (create_token(ARG, val));
}

int	is_normal_char(char c)
{
	if (c == '!' || (c >= '#' && c <= '&') || (c >= '+' && c <= '.') || (c >= '/' && c <= ':') || c == '=' || (c >= '?' && c <= 'Z') || (c >= '^' && c <= 'z'))
		return (1);
	return (0);
}

// || *input == '\\' || *input == '$' || *input == '*'
int	token_counter(char *input)
{
	int	i;

	if (*input == '\0')
		return (0);
	i = 0;
	while (*input != '\0')
	{
		while (*input == ' ' || *input == '\t')
		{
			if (*input == '\0')
				return (i);
			(input)++;
		}
		if (is_normal_char(*input))
		{
			i++;
			// printf("is_normal_char: %d\n", i);
			while (is_normal_char(*input))
			{
				if (*input == '\0')
					return (i);
				(input)++;
			}
		}
		// if (!(*input == ' ' || *input == '\t' || *input == '\n' || *input == '|' || *input == '&' || *input == ';' || *input == '(' || *input == ')' || *input == '<' || *input == '>') || *input == '"' || *input == '\'')
		// {
		// 	i++;
		// 	while (!(*input == ' ' || *input == '\t' || *input == '\n' || *input == '|' || *input == '&' || *input == ';' || *input == '(' || *input == ')' || *input == '<' || *input == '>'))
		// 	{
		// 		if (*input == '\0')
		// 			return (i);
		// 		(input)++;
		// 	}
		// }
		if (*input == '\n' || *input == '|' || *input == '&' || *input == ';' || *input == '(' || *input == ')' || *input == '<' || *input == '>')
		{
			i++;
			// printf("is_metacharacter: %d\n", i);
		}
		if (*input == '"')
		{
			i++;
			(input)++;
			while (*input != '"')
			{
				if (*input == '\0')
					error("wrong syntax!\n");
				(input)++;
			}
		}
		if (*input == '\'')
		{
			i++;
			(input)++;
			while (*input != '\'')
			{
				if (*input == '\0')
					error("wrong syntax!\n");
				(input)++;
			}
		}
		(input)++;
	}
		(input)++;
	return (i);
}

void	lexer(char *input)
{
	int		i;
	int		counter;

	input = ft_strtrim(input, " ");
	input = ft_strtrim(input, "\t");
	counter = token_counter(input);
	printf("Tokens: %d\n", counter);
	get_data()->tokens = (t_tkn **) malloc(counter * sizeof(t_tkn *));
	i = 0;
	while (i < counter)
	{
		get_data()->tokens[i] = get_next_tkn(&input);
		if (get_data()->tokens[i]->type == END)
			break ;
		printf("Token type: %d, Value: %s\n",
			get_data()->tokens[i]->type, get_data()->tokens[i]->val);
		i++;
	}
}