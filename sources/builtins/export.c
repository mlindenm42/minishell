/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 19:36:15 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//prints all exported variables (this doesn't include _)
//add error handling later malloc!!!
//function shouldnt change env
//and is generated each time minishell is run
// varible _ is not printed
static void	printexport(t_errdata *err)
{
	char	**envsorted;
	int		i;
	int		n;
	char	*end;
	char	*name;

	n = arr_len(err->envp);
	envsorted = malloc(n * sizeof(char *));
	envsorted = copy_arr(envsorted, err->envp);
	i = 0;
	arr_sort(envsorted, n - 1);
	while (envsorted[i] != NULL)
	{
		end = ft_strchr(envsorted[i], '=');
		if (ft_strncmp(envsorted[i], "_=", 2) != 0 && end != NULL)
		{
			name = ft_substr(envsorted[i], 0, end - envsorted[i], err);
			printf("declare -x %s=\"%s\"\n", name, getenv1(name, err->envp));
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

static void	replace(char *envp[], t_cmdtable *row, t_errdata *err)
{
	int		i;
	char	*end;
	char	*temp;

	end = ft_strchr(*row->curr_a, '=');
	i = 0;
	while (row->curr_a[0][i] != '=' && row->curr_a[0][i] != '\0')
		i++;
	temp = NULL;
	row->curr_a[0][i] = '\0';
	temp = ft_strdup(*row->curr_a, err);
	row->curr_a[0][i] = '=';
	replace_var(temp, end + 1, envp, err);
}

void	export(t_cmdtable *row, char *envp[], t_errdata *err)
{
	int		i;

	if (row->nargs == 1)
		printexport(err);
	else
	{
		row->curr_a = &row->args[1];
		while (row->curr_a <= &row->args[row->nargs - 1])
		{
			i = 0;
			while (row->curr_a[0][i] != '=' && row->curr_a[0][i] != '\0')
				i++;
			if (hasvar(envp, *row->curr_a, i + 1))
				replace(envp, row, err);
			else
				envappend(*row->curr_a, envp);
			row->curr_a++;
		}
	}
}
