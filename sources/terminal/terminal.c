/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:57:23 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 14:09:00 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// handles ctrl-C. Displays a new prompt on a new line.
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

// handles ctrl-D. Exits the shell.
void	handle_ctrl_d(t_errdata *err)
{
	if (err->statstr != NULL)
		free(err->statstr);
	printf("exit\n");
	exit(EXIT_FAILURE);
}

// handles ctrl-\. Does nothing.
void	handle_ctrl_backslash(int signal)
{
	if (signal == SIGQUIT)
		rl_redisplay();
}

// This function configures the terminal settings to hide the control characters
// and sets the prompt for a program called "MINISHELL."
static void	setup_terminal(void)
{
	struct termios	settings;

	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
	get_data()->prompt = "MINISHELL : ";
}

// This function sets up a terminal, processes user input in a loop, and handles
// signals, including Ctrl+C and Ctrl+\, while maintaining a history of input
// and executing commands.
void	terminal(char *envp[], t_errdata *err)
{
	setup_terminal();
	while (1)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, handle_ctrl_backslash);
		signal(SIGTSTP, SIG_IGN);
		get_data()->input = readline(get_data()->prompt);
		if (get_data()->input == NULL)
		{
			handle_ctrl_d(err);
			break ;
		}
		if (*get_data()->input)
			add_history(get_data()->input);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		lexer(get_data()->input);
		execute(envp, err);
		// free(get_data()->input);
		get_data()->input = NULL;
		// free_tokens();
	}
	rl_clear_history();
}
