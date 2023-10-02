/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/02 19:22:14 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//takes a string from env and checks if it's a variable from arguments
/* int	hasvar(char *str, t_cmdtable *row)
{
	int	i;
	int	len;

	i = 1;
	while (i <= row->nargs - 1)
	{
		len = ft_strlen(row->args[i]);
		if (ft_strnstr(str, row->args[i], len) != NULL
			&& (str[len] == '=' || str[len] == '\0'))
			return (1);
		i++;
	}
	return (0);
} */

/* int	unsetif(char *str, t_cmdtable *row, char *envp[])
{
	int	len;

	row->curr_a = &row->args[1];
	while (row->curr_a <= &row->args[row->nargs - 1])
	{
		len = ft_strlen(*row->curr_a);
		if (ft_strncmp(str, *row->curr_a, len) == 0
			&& (str[len] == '=' || str[len] == '\0'))
			{
				printf("found %s\n", *row->curr_a);
				replace_var(*row->curr_a, NULL, envp, UNSET);
			}
		row->curr_a++;
	}
	return (0);
} */

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
				{unset_var(*row->curr_a, envp);
					break;}
				i++;
		}
		row->curr_a++;
	}
}

/*
deletes variables from env and shifts the rest acoordingly
 */
/* void	unset(t_cmdtable *row, char *envp[])
{
	int	i;
	int	shift;
	int	n;

	i = 0;
	shift = 0;
	n = arr_len(envp);
	while (i <= n - 2)
	{
		if (hasvar(envp[i], row) == TRUE)
			shift++;
		else if (shift != 0)
			envp[i - shift] = envp[i];
		i++;
	}
	while (i <= n + shift - 2)
	{
		envp[i - shift] = NULL;
		i++;
	}
} */
