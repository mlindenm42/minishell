/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/19 19:31:48 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file we have functions used only in the executor
*/
#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_exdata
{
	int		*pipefds;
	int		*filefds;
	int		status;
	pid_t	*id;
}	t_exdata;

int	inopen(char *name, int *status);
void	redir_close(int fd, int stdfd, int *status);
void	create_pipe(int *pipefd, int *status);
int createfork(t_cmdtable *row, char *envp[], t_exdata *data);
int	wait_end(t_exdata data, int pipes);
int	outopen(char *outfile, int *status);

#endif