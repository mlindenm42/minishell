/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/28 22:47:39 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//prints all env variables excluding no value format
void	printenv(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
}

//checks if env has OLDPWD and corrects it if needed
int	hasoldpwd(char *envp[])
{
	int	i;
	int	oldpwd;

	i = 0;
	oldpwd = FALSE;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
		{
			if (ft_strchr(envp[i], '=') != NULL)
				envp[i] = "OLDPWD";
			oldpwd = TRUE;
		}
		i++;
	}
	return (oldpwd);
}

char	*getenv1(char *var, char *envp[])
{
	char	*value;
	int		i;
	int		len;

	value = getenv(var);
	if (value != NULL)
		return (value);
	i = 0;
	while (envp[i] != NULL)
	{
		len = ft_strlen(var);
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			value = ft_strchr(envp[i], '=') + 1;
		i++;
	}
	return (value);
}

//edits or adds OLDPWD as in bash
void	set_loc_env(char *envp[])
{
	int	n;

	n = arr_len(envp);
	if (hasoldpwd(envp) == FALSE)
	{
		if (envp[n - 2] != NULL && envp[n - 2] == getenv("_") - 2)
		{
			envp[n - 1] = envp[n - 2];
			envp[n - 2] = "OLDPWD";
		}
		else
			envp[n - 1] = "OLDPWD";
		envp[n] = NULL;
	}
}
