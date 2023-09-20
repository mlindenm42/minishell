/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:57:23 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/20 20:52:48 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h> // printf(); FILE;
#include <readline/readline.h> // rl_replace_line(); rl_on_new_line();
// rl_redisplay(); readline(); rl_clear_history();
#include <readline/history.h> // add_history(input);
#include <signal.h> // signal(); SIGINT; SIGQUIT; SIGSTP; SIG_IGN;
#include <unistd.h> // write();
#include <termios.h> // tcgetattr(); tcsetattr(); ECHOCTL; TCSANOW;

// handles ctrl-C. Displays a new prompt on a new line.
static void	handle_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// handles ctrl-D. Exits the shell.
static void	handle_ctrl_d(void)
{
	printf("exit\n");
}

// handles ctrl-\. Does nothing.
static void	handle_ctrl_backslash(int signal)
{
	if (signal == SIGQUIT)
		rl_redisplay();
}

// gets the username(if available) and saves it in data->prompt
static void	prompt(void)
{
	if (getenv("USER") != NULL)
	{
		get_data()->prompt = getenv("USER");
		ft_strlcat(get_data()->prompt, " % ",
			ft_strlen(get_data()->prompt) + 4);
	}
	else
		get_data()->prompt = "USER % ";
}

// modifies terminal settings to disable echoing of control characters in the
// terminal's input. prints terminal with the prompt and handles the signals
void	terminal(char *envp[])
{
	struct termios	settings;

	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
	prompt();
	while (1)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, handle_ctrl_backslash);
		signal(SIGTSTP, SIG_IGN);
		get_data()->input = readline(get_data()->prompt);
		if (get_data()->input == NULL)
		{
			handle_ctrl_d();
			break ;
		}
		if (*get_data()->input)
			add_history(get_data()->input);
		execute(get_data()->input, envp);
		free(get_data()->input);
	}
	// rl_clear_history();
}
