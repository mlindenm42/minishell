/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:32:39 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/12 23:35:53 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

void	lexer(char *input)
{
	char	**test;
	int		i;

	test = ft_split(input, ' ');
	printf("%s \n", test[0]);
	i = 0;
	while (test[i] != NULL)
	{
		if (test[i] != NULL)
			free(test[i++]);
	}
	if (test != NULL)
		free(test);
}

void	handle_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_ctrl_backslash(int signal)
{
	if (signal == SIGQUIT)
		rl_redisplay();
}

void	handle_ctrl_d(void)
{
	printf("exit\n");
}

void	terminal(void)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, handle_ctrl_backslash);
		signal(SIGTSTP, SIG_IGN);
		input = readline(get_data()->prompt);
		if (input == NULL)
		{
			handle_ctrl_d();
			break ;
		}
		if (*input)
			add_history(input);
		lexer(input);
		free(input);
	}
	rl_clear_history();
}
