/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/14 16:01:26 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* checking delimiter after each newine
buffer variants
|text\n     | |delimiter\n| - don't write into the file  !!!
|texttexttex| |delimiter\n| - write the whole buffer to the file !!!
|texttexttex| - write the whole buffer to the file
|text\n     | - write the part of the buffer including \n
*/

//generates temporary file name based on row number
static char	*genpath(int i)
{
	char	*n;
	char	*fpath;

	fpath = NULL;
	n = ft_itoa(i);
	if (n != NULL)
	{
		fpath = ft_strjoin("sources/obj/tmp", n);
		free(n);
	}
	return (fpath);
}

void	handle_c(int signal)
{
	int i;
	i=0;
	if (signal == SIGINT)
	{
		ioctl(0, TIOCSTI, 4);
		//rl_replace_line("", 0);
		//rl_on_new_line();
		//rl_redisplay();
		// ioctl(0, FIONREAD, &i);
		// dprintf(2, "n sig %i\n", i);

	}
}

/*
reads from stdin untill delimiter and writes into a file
prevnl is TRUE if previous buffer ended with newline
 */
/* static int	stdintofd(char *dlm, int filefd)
{
	char	*buf;
	char	*cur;
	int		size;
	int		prevnl;
	int		isdlm;

	prevnl = TRUE;
	isdlm = FALSE;
	size = ft_strlen(dlm) + 1;
	buf = malloc((size + 1) * sizeof(char));
	if (buf == NULL)
		return (1);
	cur = buf;
	write(1, "> ", 3);
	while (isdlm == 0 || *(buf + size - 1) != '\n' || prevnl == 0)
	{
		prevnl = nlupdate(cur, isdlm, prevnl, 1);
		cur = readbuf(buf, size);
		isdlm = (ft_strncmp(buf, dlm, size - 1) == 0);
		signal(SIGINT, handle_c);
		wrtofile((isdlm == TRUE && prevnl == TRUE), filefd, cur, buf);
		prevnl = nlupdate(cur, isdlm, prevnl, 0);
	}
	free(buf);
	buf = NULL;
	return (0);
} */

static int	stdintofd(char *dlm, int filefd)
{
	char	*input;
	// int		sig;
	//char	buf[1];
	//int i;

	// sig = 0;
	//i = 0;
	input = NULL;
	while (1)
	{
		signal(SIGINT, handle_c);
		signal(SIGTSTP, SIG_IGN);
		//dprintf(2, "input after signal %s\n", input);
		if (input != NULL)
			return (SIGINT);
		input = readline("> ");
		//dprintf(2, "input after reading %s\n", input);
	
		if (ft_strcmp(input, dlm) == 0)
			break;
		// signal(SIGQUIT, handle_ctrl_backslash);
		// signal(SIGTSTP, SIG_IGN);
	/* 	if (read(0, buf, 1) == '\n')
		{
			return (SIGINT);
		} */
		//signal(SIGINT, handle_ctrl_c);
		ft_putendl_fd(input, filefd);
		free(input);
		input = NULL;
	}
	return (0);
}

//scanning inputs for here_docs
static int	inputscan(t_exedata *data, t_cmdtable *row, int i)
{
	int	k;
	int	fd;
	int	rtn;

	k = 0;
	rtn = 0;
	while (k <= row->nins - 1)
	{
		if (row->infiles[k].io == LLT)
		{
			if (data->path[i] == NULL)
				data->path[i] = genpath(i);
			if (data->path[i] != NULL)
			{
				if (access(data->path[i], F_OK) == 0)
					unlink(data->path[i]);
				fd = open(data->path[i], O_CREAT | O_RDWR, 0644);
				if (fd >= 0)
				{
					rtn = stdintofd(row->infiles[k].file, fd);
					if (rtn == 1)
						err_handler(row->err, "here_document", CNT);
					close(fd);
				}
			}
		}
		k++;
	}
	return (rtn);
}

int	heredoc(t_cmdtable *tbl, t_exedata *data)
{
	int	i;

	i = 0;
	data->path = malloc(sizeof(char *) * tbl->nrows + 1);
	if (data->path == NULL)
	{
		errfree(tbl->err, &data, &free_exedt, CNT);
		return (1);
	}
	data->path[tbl->nrows] = NULL;
	while (i <= tbl->nrows - 1)
	{
		data->path[i] = NULL;
		if (inputscan(data, &tbl[i], i) == SIGINT)
			return (SIGINT);
		i++;
	}
	return (0);
}
