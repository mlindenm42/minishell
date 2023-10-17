/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 10:18:50 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	isbuiltin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	env_change(char *cmd, int nrows)
{
	return (nrows == 1 && (ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0));
}

void	exitbuiltin(char *argv[], t_errdata *err)
{
	int		stat;
	char	*tmp;

	stat = 0;
	if (argv[1] != NULL && argv[2] == NULL)
	{
		stat = ft_atoi(argv[1]);
		if (stat == 0)
		{
			tmp = ft_strjoin(argv[1], ": numeric argument required", err);
			custom_err("bash: exit", tmp, err);
			stat = 255;
		}
	}
	printf("exit\n");
	free_data(&err->gc, err->gc.elem);
	exit(stat);
}
