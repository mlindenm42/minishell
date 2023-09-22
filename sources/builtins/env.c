/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/23 00:10:21 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//prints all env variables
void	printenv(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

//allocates memory for local environment and copies the initial environment
void	set_loc_env(char *envp[], t_errdata *err)
{
	int	i;
	int	n;

	i = 0;
	n = arr_len(envp);
	err->envp_loc = malloc(sizeof(char*) * n);
	while (envp[i] != NULL)
	{
		err->envp_loc[i] = ft_strdup(envp[i]);
		i++;
	}
	err->envp_loc[i] = NULL;
}

//increase the size of local environment to add more variables
char	**expand_loc_env(char **envp_loc, int nvar)
{
	char **tmp;
	int	n;

	tmp = envp_loc;
	n = arr_len(envp_loc);
	envp_loc = malloc(sizeof(char*) * (n + nvar));
	envp_loc = copy_arr(envp_loc, tmp);
	envp_loc[n + nvar - 2] = NULL;
	free(tmp);
	return (envp_loc);
}

//later
void printexport(char **envp_loc)
{
	printf("prints variables");
}


void export(char **envp_loc, t_cmdtable *row)
{
	int i;
	int n;

	if (row->nargs == 1)
		printexport(row->err->envp_loc);
	else
	{
		i = 1;
		row->err->envp_loc = expand_loc_env(row->err->envp_loc, row->nargs - 1);
		n = arr_len(row->err->envp_loc);
		while (i <= row->nargs - 1)
		{
			row->err->envp_loc[n - 2 + i] = ft_strdup(row->args[i]);
			i++;
		}
	}
}

/* void	addenv(char *envp[], char *name, char *value)
{
	int	i;
	int	n;

	i = 0;
	n = arr_len(envp);

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
} */

