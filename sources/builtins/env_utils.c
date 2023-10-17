/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:45:49 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 19:39:17 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//if a variable exists returns the pointer
//to its start
//vname only first l chars!!!
static char	*var(char *vname, char *envp[], int l)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], vname, l) == 0
			&& (envp[i][l] == '=' || envp[i][l] == '\0' ))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static int	vlen(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	replace_var(char *var, char *val, char *envp[], t_errdata *err)
{
	int		index;
	int		i;
	char	*new_var;
	char	*new_entry;

	index = -1;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var))
			== 0 && envp[i][ft_strlen(var)] == '=')
		{
			index = i;
			break ;
		}
		i++;
	}
	if (index != -1)
	{
		new_var = create_elem(&err->gc, sizeof(char), ft_strlen(var) + ft_strlen(val) + 2);
		if (new_var != NULL)
		{
			strcpy(new_var, var);
			strcat(new_var, "=");
			strcat(new_var, val);
			envp[index] = new_var;
		}
		else
		{
			fprintf(stderr, "Memory allocation failed.\n");
			exit(1);
		}
	}
	else
	{
		new_entry = create_elem(&err->gc, sizeof(char), ft_strlen(var) + ft_strlen(val) + 2);
		if (new_entry != NULL)
		{
			strcpy(new_entry, var);
			strcat(new_entry, "=");
			strcat(new_entry, val);
			i = 0;
			while (envp[i] != NULL)
				i++ ;
			envp[i] = new_entry;
			envp[i + 1] = NULL;
		}
		else
		{
			fprintf(stderr, "Memory allocation failed.\n");
			exit(1);
		}
	}
}

void	unset_var(char *vname, char *envp[])
{
	char	*start;
	char	*dst;
	char	*end;
	char	*env_end;

	start = var(vname, envp, vlen(vname));
	end = start + ft_strlen(start);
	dst = start;
	env_end = getenvmem_end(envp);
	if (env_end != end)
		ft_memmove(dst, end + 1, env_end - end);
	ft_bzero(env_end + (dst - end) - 1, end + 1 - dst);
	if (env_end == end)
		envp[arr_len(envp) - 2] = NULL;
	else
		shiftenv(start, envp, start - end - 1, env_end);
}
