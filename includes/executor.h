/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/22 00:56:06 by mrubina          ###   ########.fr       */
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
	int		*filefd;
	int		status;
	int		pbreak;
	pid_t	*id;
}	t_exdata;

# define NB 0
# define BR 1
# define EO 2
# define EB 3



void	redir_close(int fd, int stdfd, int *status);
void	create_pipe(int *pipefd, int *status);
void create_child(t_cmdtable *row, char *envp[], t_exdata *data, int flag);
int	wait_end(t_exdata data, int pipes);
int	outopen(t_cmdtable *row,  int *fd, int *flag);
int	inopen(t_cmdtable *row, int *fd, int *flag);

#endif