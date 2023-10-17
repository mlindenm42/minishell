/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 02:30:32 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checks if env has PWD
int	haspwd(char *envp[])
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
int	hasoldpwd(char *envp[])
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

int	cd(char *argv[], char *envp[], t_errdata *err)
{
	char	*copy;
	char	*temp;

	copy = getcwd(NULL, 0);
	if (chdir(argv[1]) == -1)
	{
		printf("MINISHELL : cd %s: No such file or directory\n", argv[1]);
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
	burn_it_down(&err->gc, err->gc.dump);
	exit(stat);
}
