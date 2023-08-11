/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/11 15:52:04 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_data	*get_data(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

void	lexer(char *input)
{
	char	**test;

	test = ft_split(input, ' ');
	printf("%s \n", test[0]);
}

void	prompt(void)
{
	char	*prompt;
	char	*input;

	prompt = getenv("USER");
	ft_strlcat(prompt, " % ", ft_strlen(prompt) + 4);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		lexer(input);
		free(input);
	}
}

int	main(void)
{
	prompt();
	return (0);
}
