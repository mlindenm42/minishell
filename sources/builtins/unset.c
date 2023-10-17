/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 21:32:14 by mlindenm         ###   ########.fr       */
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

void	unset(t_cmdtable *row, char *envp[])
{
	int	i;
	int	len;

	row->curr_a = &row->args[1];
	while (row->curr_a <= &row->args[row->nargs - 1])
	{
		len = ft_strlen(*row->curr_a);
		i = 0;
		while (envp[i] != NULL)
		{
			if (ft_strncmp(envp[i], *row->curr_a, len) == 0
				&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			{
				unset_var(*row->curr_a, envp);
				break ;
			}
			i++;
		}
		row->curr_a++;
	}
}
