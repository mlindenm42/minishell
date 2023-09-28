/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/27 19:29:50 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//takes a string from env and checks if it's a variable from arguments
int	hasvar(char *str, t_cmdtable *row)
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
}

/*
deletes variables from env and shifts the rest acoordingly
 */
void	unset(t_cmdtable *row, char *envp[])
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
}
