/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 08:11:38 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
