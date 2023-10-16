/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
<<<<<<<<< Temporary merge branch 1
/*   Updated: 2023/10/15 20:10:18 by mlindenm         ###   ########.fr       */
=========
/*   Updated: 2023/10/16 00:26:51 by mrubina          ###   ########.fr       */
>>>>>>>>> Temporary merge branch 2
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->token, tkn->val);
//printf("nd token%i, %s\n", tkn->token, tkn->val);
//printf("%i\n", pipes);

//redirecting file descriptor to stdin/stddout and closing it
void	redir_close(int fd, int stdfd, t_errdata *err)
{
	if (dup2(fd, stdfd) == -1)
		err_handler(err, NULL, CNT);
	if (err->stop == CNT && close(fd) == -1)
		err_handler(err, NULL, CNT);
}

int	create_pipe(t_exedata *data, t_errdata *err)
{
	int	pp[2];

	if (err->stop == CNT && data->pbreak != BR)
	{
		if (pipe(pp) == -1)
			errfree(err, data, &free_exedt, STP);
		data->infd = pp[0];
		data->outfd = pp[1];
		if (err->stop == STP)
			free_exedt(data);
	}
	return (err->stop);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	// size_t	i;
	size_t	n1;
	size_t	n2;

	// i = 0;
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	if (n1 != n2)
		return (1);
	else
		return (ft_strncmp(s1, s2, n1));
}

/*
 */
void	exe_builtin(t_cmdtable *row, char *envp[], t_errdata *err, int ch_flag)
{
	t_cmdtable *tbl;

	if (ft_strcmp(row->args[0], "echo") == 0)
		echo(row->args);
	else if (ft_strcmp(row->args[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(row->args[0], "env") == 0)
		printenv(envp);
	else if (ft_strcmp(row->args[0], "export") == 0)
		export(row, envp);
	else if (ft_strcmp(row->args[0], "unset") == 0)
		unset(row, envp);
	else if(ft_strcmp(row->args[0], "cd") == 0)
		cd(row->args);
	else if(ft_strcmp(row->args[0], "exit") == 0)
		exitbuiltin(row->args, err);
	if (ch_flag == 0)
	{
		//!!!
		//free_exedt(err->edata);//!!!
		//free_rows(row + (row->nrows - 1 - row->pipeid));
		tbl = row - row->pipeid;
		freeall(err);
		// free(get_data()->prompt);
		// free(get_data()->input);
		// free(get_data()->tokens);
		//free_rows(row + (row->nrows - 1 - row->pipeid));
		//free(row - (row->pipeid - 1));
		exit(0);
	}
}

/* redirects stdout to the pipe, creates child process and executes command */
int	create_child(t_cmdtable *row, char *envp[], t_errdata *err)
{
	redir_close(err->edata->outfd, 1, err);
	//printf("arg12 %s\n", row->args[1]);
	err->edata->id[row->pipeid] = fork();
	if (err->edata->id[row->pipeid] == -1)
		err_handler(err, NULL, NXT);
	else if (err->edata->id[row->pipeid] == 0)
	{
		close(err->edata->infd);
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, handle_ctrl_backslash);
		signal(SIGTSTP, SIG_IGN);
		err->edata->status = 0;
		if (isbuiltin(row->args[0]))
			exe_builtin(row, envp, err, 0);
		else if (row->cmd == NULL)
			cmderr1(err, row->args[0], envp, CNT); //!!!
		else if (execve(row->cmd, row->args, envp) == -1)
			cmderr(err, row->cmd, CNT);
	}
	else
		close(err->edata->outfd);
	return (err->stop);
}
