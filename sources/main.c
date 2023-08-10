/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/10 19:08:54 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
