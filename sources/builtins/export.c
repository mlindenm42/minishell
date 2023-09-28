/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/28 20:37:55 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//prints all exported variables (this doesn't include _)
//add error handling later
//function shouldnt change env
//OLDPWD is shown in export but not in env
//and is generated each time minishell is run
// varible _ is not printed

void	printexport(char **envp)
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
			printf("declare -x %s=\"%s\"\n", name, getenv(envsorted[i]));
			free(name);
		}
		else if (ft_strncmp(envsorted[i], "_=", 2) != 0)
			printf("declare -x %s\n", envsorted[i]);
		i++;
	}
	free(envsorted);
}

//checks if a certain variable without a value is present in env
int	inenv_nv(char *var, char *envp[])
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strcmp(envp[i], var) != 1)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/* checks if a variable is present in env - 3 cases
	new variable has a value
	new variable has no value but the old one does
	both variables have no value
*/
int	inenv(char *arg, char *envp[])
{
	char	*end;
	char	*name;
	char	*val;

	end = ft_strchr(arg, '=');
	if (end != NULL)
	{
		name = ft_substr(arg, 0, end - arg);
		val = getenv(name);
		free(name);
		if (val == NULL)
			return (FALSE);
		return (TRUE);
	}
	else if (getenv(arg) != NULL)
		return (TRUE);
	else
		return (inenv_nv(arg, envp));
}

/* scans environment for variables and replaces them with arguments */
void	envscan(t_cmdtable *row, char *envp[])
{
	int		i;
	int		len;
	char	*end;

	i = 0;
	while (i <= arr_len(envp) - 2)
	{
		row->curr_a = &row->args[1];
		while (row->curr_a <= &row->args[row->nargs - 1])
		{
			end = ft_strchr(*row->curr_a, '=');
			if (end != NULL)
			{
				if (ft_strncmp(envp[i], *row->curr_a, end - *row->curr_a) == 0)
					envp[i] = *row->curr_a;
			}
			row->curr_a++;
		}
		i++;
	}
}

void	export(t_cmdtable *row, char *envp[])
{
	int		i;
	int		n;
	char	*undsc;

	if (row->nargs == 1)
		printexport(envp);
	else
	{
		envscan(row, envp);
		row->curr_a = &row->args[1];
		i = 0;
		n = arr_len(envp);
		if (envp[n - 2] != NULL && envp[n - 2] == getenv("_") - 2)
		{
			undsc = envp[n - 2];
			n--;
		}
		while (row->curr_a <= &row->args[row->nargs - 1])
		{
			if (inenv(*row->curr_a, envp) == FALSE)
			{
				//ft_strlcpy(row->err->envmem_end + 1, *row->curr_a, ft_strlen(*row->curr_a) + 1);
				//envp[n - 1 + i] = row->err->envmem_end + 1;
				envp[n - 1 + i] = *row->curr_a;
				//row->err->envmem_end = row->err->envmem_end + ft_strlen(*row->curr_a) + 1;
				//printf("n %s\n", getenv("var1"));
				i++;
			}
			row->curr_a++;
		}
		envp[n - 1 + i] = undsc;
		envp[n + i] = NULL;
		//printf("n %s\n", getenv("var4"));
	}
}
