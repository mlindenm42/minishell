/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/10 19:46:30 by mlindenm         ###   ########.fr       */
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

int	main(void)
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
		printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}
