/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 06:18:02 by mlindenm         ###   ########.fr       */
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

//returns pointer to the end of the last used character of the
//allocated memory
//we use memory after it for created variables
char	*getenvmem_end(char *envp[])
{
	char	*end;

	while (*envp != NULL)
		envp++;
	end = *(envp - 1);
	while (*end != '\0')
		end++;
	return (end);
}

//sets pointers for env variables to their memory respectively
//after changes in that memory
void	shiftenv(char *var, char *envp[], int shift, char *end)
{
	int	i;

	i = 0;
	while (envp[i] != var)
		i++;
	i++;
	while (envp[i + 1] != NULL)
	{
		if (envp[i + 1] >= var && envp[i + 1] <= end)
			envp[i] = envp[i + 1] + shift;
		else
			envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
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

void	set_loc_env(char *envp[], t_errdata *err)
{
	char	*shlvl;

	shlvl = ft_itoa((ft_atoi(getenv1("SHLVL", envp)) + 1), err);
	replace_var("SHLVL", shlvl, envp);
}
