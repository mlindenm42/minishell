/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/17 20:46:19 by mrubina          ###   ########.fr       */
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

/* 	else if(ft_strcmp(argv[0], "cd") == 0)
		cd(argv);
	else if(ft_strcmp(argv[0], "pwd") == 0)
		pwd(argv);
	else if(ft_strcmp(argv[0], "export") == 0)
		export(argv);
	else if(ft_strcmp(argv[0], "unset") == 0)
		unset(argv);
	else if(ft_strcmp(argv[0], "env") == 0)
		env(argv);
	else if(ft_strcmp(argv[0], "exit") == 0)
		changedir(argv); */
