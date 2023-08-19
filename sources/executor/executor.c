/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/19 19:55:08 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//printf("end pipe%i, %s\n", tkn->token, tkn->val);
//printf("nd token%i, %s\n", tkn->token, tkn->val);
//printf("%i\n", pipe_cnt);


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
	
	data.filefds = malloc(sizeof(int)*(tbl->nouts + tbl->nins));
	data.pipefds = malloc(sizeof(int)*tbl->pipe * 2);
	data.id = malloc(sizeof(pid_t)*tbl->nrows);
	i = 0;
	/* handling infiles
	in case of an error at least in one of the files process doesn't start in this pipeline
	the next pipeline receives an empty input
	in case of no error only the last infile is used!!!
	for each pipe explicit input of that pipe overrides output from the previous pipe
	*/
	//we selected infile in the previous step, now open infile
	//data.filefds[0] = inopen(tbl->infiles[0].file, data.status);
	/* execution
	
	*/

//exit(0);
	//redir_close(data.filefds[0], 0, &data.status);
	//printf("ddfd%i\n", tbl->nrows - 1);
	while (i <= tbl->nrows - 2)
	{
		create_pipe(&data.pipefds[2 * i], &data.status);
		createfork(&tbl[i], envp, &data);
		close(data.pipefds[2*i + 1]);
		redir_close(data.pipefds[2 * i], 0, &data.status);
		i++;
	}
	data.filefds[1] = outopen(tbl[i].outfiles[0].file, &data.status);
	redir_close(data.filefds[1], 1, &data.status);
	//printf("ddfd%s\n", tbl[i].cmd);
	createfork(&tbl[i], envp, &data);
	wait_end(data, tbl->nrows);
//when there is an out in a pipe which is not the last the pipe after it has empty input
}
