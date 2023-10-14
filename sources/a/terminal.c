/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:57:23 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/14 01:08:21 by mrubina          ###   ########.fr       */
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
	free(get_data()->prompt);
	if (err->statstr != NULL)
	 	free(err->statstr);
	// if (err->edata != NULL && err->edata->id != NULL)
	// 	free(err->edata->id);
	if (get_data()->tokens != NULL)
		free(get_data()->tokens);
/* 	if (err->tbl != NULL)
	{free_rows(&(err->tbl[err->tbl->nrows - 1]));
	free(err->tbl);} */
	printf("exit\n");
}

// handles ctrl-\. Does nothing.
void	handle_ctrl_backslash(int signal)
{
	if (signal == SIGQUIT)
		rl_redisplay();
}

// gets the username(if available) and saves it in data->prompt
static void	prompt(void)
{
	if (getenv("USER") != NULL)
	{
		get_data()->prompt = ft_strjoin(getenv("USER"), " % ");
	/* 	get_data()->prompt = ft_strdup(getenv("USER"));
		ft_strlcat(get_data()->prompt, " % ",
			ft_strlen(get_data()->prompt) + 4); */
	}
	else
		get_data()->prompt = "USER % ";
}

// modifies terminal settings to disable echoing of control characters in the
// terminal's input. prints terminal with the prompt and handles the signals
void	terminal(char *envp[], t_errdata *err)
{
	struct termios	settings;
	char *input;

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
			handle_ctrl_d(err);
			break ;
		}
		if (*get_data()->input)
			add_history(get_data()->input);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		execute(get_data()->input, envp, err);
		free(get_data()->input);
	}
	rl_clear_history();
}
