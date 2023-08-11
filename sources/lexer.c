/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:32:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/11 18:34:49 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	lexer(char *input)
{
	char	**test;

	test = ft_split(input, ' ');
	printf("%s \n", test[0]);
}

void	prompt(void)
{
	char	*input;
	char	*name;

	name = getenv("USER");
	get_data()->prompt = (char *) malloc((ft_strlen(name) + 4) * sizeof(char));
	printf("HALLO\n");
	// if (get_data()->prompt == NULL)
	// 	error("malloc prompt failed");
	get_data()->prompt = name;
	// ft_strlcat(get_data()->prompt, " % ", ft_strlen(get_data()->prompt) + 4);
	while (1)
	{
		input = readline(get_data()->prompt);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		lexer(input);
		free(input);
	}
	// free(get_data()->prompt);
}
