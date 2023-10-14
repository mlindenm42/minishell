/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/14 06:53:11 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//prints all exported variables (this doesn't include _)
//add error handling later malloc!!!
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
			printf("declare -x %s=\"%s\"\n", name, getenv1(name, envp));
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
			return (1);
		i++;
	}
	return (0);
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
		val = getenv1(name, envp);
		free(name);
		if (val == NULL)
			return (0);
		return (1);
	}
	else if (getenv1(arg, envp) != NULL)
		{
			//printf("var %s\n", getenv1(arg, envp));
			return (1);}
	else
		return (inenv_nv(arg, envp));
}

//adds a string to env
void envappend(char *str, char *envp[])
{
	char	*env_end;
	int		n;

	n = arr_len(envp);
	env_end = getenvmem_end(envp);
	ft_strlcpy(env_end + 1, str, ft_strlen(str) + 1);
	envp[n - 1] = env_end + 1;
	envp[n] = NULL;
}

//moves _ variable to the end of env
/* void	movetoend(char *start, char *envp[])
{
	char	*str_end;
	char	*env_end;
	int		n;

	n = arr_len(envp);
	env_end = getenvmem_end(envp);
	ft_strlcpy(env_end + 1, start, ft_strlen(start) + 1);
	envp[n - 1] = env_end + 1;
	envp[n] = NULL;
	replace_var("_", NULL, envp, UNSET);
} */

/* scans environment for variables and replaces them with arguments
replaces only if new value isn't NULL
*/
//!!! malloc errors
void	envscan(t_cmdtable *row, char *envp[])
{
	int		i;
	// int		len;
	char	*end;
	char*	vname;

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
				{
					vname = ft_substr(*row->curr_a, 0, end - *row->curr_a);
					replace_var(vname, end + 1, envp);
					free(vname);
				}
			}
			row->curr_a++;
		}
		i++;
	}
}

/* void	export(t_cmdtable *row, char *envp[])
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
		if (envp[n - 2] != NULL && envp[n - 2] == getenv1("_", envp) - 2)
		{
			undsc = envp[n - 2];
			n--;
		}
		while (row->curr_a <= &row->args[row->nargs - 1])
		{
			if (inenv(*row->curr_a, envp) == FALSE)
			{
				ft_strlcpy(row->err->envmem_end + 1, *row->curr_a, ft_strlen(*row->curr_a) + 1);
				envp[n - 1 + i] = row->err->envmem_end + 1;
				envp[n - 1 + i] = *row->curr_a;
				row->err->envmem_end = row->err->envmem_end + ft_strlen(*row->curr_a) + 1;
				//printf("n %s\n", getenv1("var1", envp));
				i++;
			}
			row->curr_a++;
		}
		envp[n - 1 + i] = undsc;
		envp[n + i] = NULL;
		//printf("n %s\n", getenv("var4"));
	}
} */
//
/* void	export(t_cmdtable *row, char *envp[])
{
	int		n;
	char	*undsc;
	char	*end;

	if (row->nargs == 1)
		printexport(envp);
	else
	{
		envscan(row, envp);
		row->curr_a = &row->args[1];
		while (row->curr_a <= &row->args[row->nargs - 1])
		{
			if (inenv(*row->curr_a, envp) == FALSE)
			{
				//printf("var %s\n", *row->curr_a);
				envappend(*row->curr_a, envp);
				n = arr_len(envp);
				end = getenvmem_end(envp);
				ft_strlcpy(end + 1, *row->curr_a, ft_strlen(*row->curr_a) + 1);
				envp[n - 1] = end + 1;
				envp[n] = NULL;
			}
			row->curr_a++;
		}
	}
} */

void	export(t_cmdtable *row, char *envp[])
{
	int	i;
	char	*end;
	int		is_set;

	if (row->nargs == 1)
		printexport(envp);
	else
	{
		row->curr_a = &row->args[1];
		while (row->curr_a <= &row->args[row->nargs - 1])
		{
			is_set = 0;
			end = ft_strchr(*row->curr_a, '=');
			i = 0;
			while (envp[i] != NULL)
			{
				if (ft_strncmp(envp[i], *row->curr_a, varlen(*row->curr_a)) == 0)
				{
					if (end != NULL)
						replace_var(*row->curr_a, end + 1, envp);
					is_set = 1;
					break;
				}
				i++;
			}
			if (is_set == 0)
				envappend(*row->curr_a, envp);
			row->curr_a++;
		}
	}
}