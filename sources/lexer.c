/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:32:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/17 00:23:55 by mlindenm         ###   ########.fr       */
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

t_token	*get_next_token(char **input)
{
	char	val[256];
	int		i;

	while (**input == ' ' || **input == '\t')
		(*input)++;
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

void	lexer(char *input)
{
	int		i;

	get_data()->tokens = (t_token **) malloc(100 * sizeof(t_token *));
	i = 0;
	while (1)
	{
		get_data()->tokens[i] = get_next_token(&input);
		if (get_data()->tokens[i]->type == END)
			break ;
		printf("Token type: %d, Value: %s\n",
			get_data()->tokens[i]->type, get_data()->tokens[i]->val);
		i++;
	}
}
