/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:57:23 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/15 21:00:05 by mlindenm         ###   ########.fr       */
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
	// if (err->edata != NULL && err->edata->id != NULL)
	// 	free(err->edata->id);
/* 	if (err->tbl != NULL)
	{free_rows(&(err->tbl[err->tbl->nrows - 1]));
	free(err->tbl);} */
	printf("exit\n");
	exit(EXIT_FAILURE);
}

// handles ctrl-\. Does nothing.
void	handle_ctrl_backslash(int signal)
{
	if (signal == SIGQUIT)
		rl_redisplay();
}

void	free_tokens(void)
{
	int	i;

	i = 0;
	if (get_data()->tokens != NULL)
	{
		while (i < get_data()->tokenslength)
		{
			if (get_data()->tokens[i].val != NULL)
			{
				free(get_data()->tokens[i].val);
				get_data()->tokens[i].val = NULL;
			}
			i++;
		}
		if (get_data()->tokens != NULL)
		{
			free(get_data()->tokens);
			get_data()->tokens = NULL;
		}
	}
}

// gets the username(if available) and saves it in data->prompt
static void	prompt(void)
{
	// if (getenv("USER") != NULL)
	// {
	// 	get_data()->prompt = ft_strjoin(getenv("USER"), " % ");
	// /* 	get_data()->prompt = ft_strdup(getenv("USER"));
	// 	ft_strlcat(get_data()->prompt, " % ",
	// 		ft_strlen(get_data()->prompt) + 4); */
	// }
	// else
		get_data()->prompt = "USER % ";
}

// modifies terminal settings to disable echoing of control characters in the
// terminal's input. prints terminal with the prompt and handles the signals
void	terminal(char *envp[], t_errdata *err)
{
	struct termios	settings;
	// char *input;

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
		lexer(get_data()->input);
		execute(envp, err);
		free(get_data()->input);
		get_data()->input = NULL;
		free_tokens();
	}
	rl_clear_history();
}
