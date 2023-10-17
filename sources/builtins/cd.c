/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 17:25:43 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checks if env has PWD
static int	haspwd(char *envp[])
{
	int	i;
	int	pwd;

	i = 0;
	pwd = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			pwd = 1;
		}
		i++;
	}
	return (pwd);
}

//checks if env has OLDPWD
static int	hasoldpwd(char *envp[])
{
	int	i;
	int	oldpwd;

	i = 0;
	oldpwd = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			oldpwd = 1;
		}
		i++;
	}
	return (oldpwd);
}

void	pwd(void)
{
	char	*curdir;

	curdir = getcwd(NULL, 0);
	if (curdir != NULL)
	{
		printf("%s\n", curdir);
		free(curdir);
	}
}

int	cd(char *argv[], char *envp[], t_errdata *err)
{
	char	*copy;
	char	*temp;

	copy = getcwd(NULL, 0);
	if (argv[1] != NULL && chdir(argv[1]) == -1)
	{
		err_handler(err, argv[1], CNT);
		return (1);
	}
	temp = ft_strjoin("PWD=", getcwd(NULL, 0), err);
	if (haspwd(envp))
		replace_var("PWD=", getcwd(NULL, 0), envp);
	else
		envappend(temp, envp);
	temp = ft_strjoin("OLDPWD=", copy, err);
	if (hasoldpwd(envp))
		replace_var("OLDPWD=", copy, envp);
	else
		envappend(temp, envp);
	return (0);
}
