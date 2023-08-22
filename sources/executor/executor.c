/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/22 14:08:56 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->token, tkn->val);
//printf("nd token%i, %s\n", tkn->token, tkn->val);
//printf("%i\n", pipe_cnt);
			//ft_putnbr_fd(flag, 2);
			//ft_putchar_fd('\n', 2);

//takes command table and executes commmand
/* int		pipe;
	char	*cmd;
	char	**args;
	t_iof	*infiles;
	t_iof	*outfiles;
	char	**curr_a;
	t_iof	*curr_i;
	t_iof	*curr_o;
	int		nargs;
	int		nins;
	int		nouts; */


void	executor (t_cmdtable *tbl, char *envp[])
{
	t_cmdtable	*row;
	t_exdata data;
	int		i;

	data.pbreak = NB;
	data.filefd = malloc(sizeof(int)*2);
	data.pipefds = malloc(sizeof(int)*tbl->pipeid * 2);
	data.id = malloc(sizeof(pid_t)*tbl->nrows);
	i = 0;
	if (tbl->nins != 0)
	{
		inopen(tbl, &data.filefd[0], &data.pbreak);
		if (data.pbreak == EO && tbl->nrows > 1)
			i++;
		redir_close(data.filefd[0], 0, &data.status);
	}
	while (i <= tbl->nrows - 2)
	{
		if (i != 0 && tbl[i].nins != 0)
		{
			inopen(&tbl[i], &data.filefd[0], &data.pbreak);
			redir_close(data.filefd[0], 0, &data.status);
		}
		if (i != tbl->nrows - 1 && tbl[i].nouts != 0)
		{
			outopen(&tbl[i], &data.filefd[1], &data.pbreak);
			data.pbreak++;
			redir_close(data.filefd[1], 1, &data.status);
		}
		if (data.pbreak <= BR)
		{
			create_pipe(&data.pipefds[2 * i], &data.status);
			create_child(&tbl[i], envp, &data, data.pbreak);
			if (data.pbreak == NB)
			{
				if (close(data.pipefds[2*i + 1]) == -1)
					perror("");
				redir_close(data.pipefds[2 * i], 0, &data.status);
			}
		}
		data.pbreak = NB;
		i++;
	}
	outopen(&tbl[i], &data.filefd[1], &data.pbreak);
	redir_close(data.filefd[1], 1, &data.status);
	create_child(&tbl[i], envp, &data, data.pbreak);
	wait_end(data, tbl->nrows);
}
