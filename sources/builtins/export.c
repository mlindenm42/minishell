/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 08:15:10 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//prints all exported variables (this doesn't include _)
//add error handling later malloc!!!
//function shouldnt change env
//and is generated each time minishell is run
// varible _ is not printed
static void	printexport(char **envp)
{
	char	**envsorted;
	int		i;
	int		n;
	char	*end;
	char	*name;

	n = arr_len(envp);
	envsorted = malloc(n * sizeof(char *));
	envsorted = copy_arr(envsorted, envp);
	i = 0;
	arr_sort(envsorted, n - 1);
	while (envsorted[i] != NULL)
	{
		end = ft_strchr(envsorted[i], '=');
		if (ft_strncmp(envsorted[i], "_=", 2) != 0 && end != NULL)
		{
			name = ft_substr(envsorted[i], 0, end - envsorted[i]);
			printf("declare -x %s=\"%s\"\n", name, getenv1(name, envp));
			free(name);
		}
		else if (ft_strncmp(envsorted[i], "_=", 2) != 0)
			printf("declare -x %s\n", envsorted[i]);
		i++;
	}
	free(envsorted);
}

//checks if env has variable
static int	hasvar(char *envp[], char *str, int len)
{
	int	i;
	int	has;

	i = 0;
	has = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, len) == 0)
		{
			has = 1;
		}
		i++;
	}
	return (has);
}

//adds a string to env
void	envappend(char *str, char *envp[])
{
	char	*env_end;
	int		n;

	n = arr_len(envp);
	env_end = getenvmem_end(envp);
	ft_strlcpy(env_end + 1, str, ft_strlen(str) + 1);
	envp[n - 1] = env_end + 1;
	envp[n] = NULL;
}

void	export(t_cmdtable *row, char *envp[])
{
	int		i;
	char	*end;

	if (row->nargs == 1)
		printexport(envp);
	else
	{
		row->curr_a = &row->args[1];
		while (row->curr_a <= &row->args[row->nargs - 1])
		{
			i = 0;
			while (row->curr_a[0][i] != '=')
				i++;
			if (hasvar(envp, *row->curr_a, i + 1))
			{
				end = ft_strchr(*row->curr_a, '=');
				replace_var(*row->curr_a, end + 1, envp);
			}
			else
				envappend(*row->curr_a, envp);
			row->curr_a++;
		}
	}
}
