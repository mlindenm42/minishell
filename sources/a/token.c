/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:45:47 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/15 23:47:15 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(void)
{
	int	i;

	i = 0;
	if (get_data()->tokens != NULL)
	{
		while (i < get_data()->tokenslength)
		{
			if (get_data()->tokens[i].val != NULL)
			{
				free(get_data()->tokens[i].val);
				get_data()->tokens[i].val = NULL;
			}
			i++;
		}
		if (get_data()->tokens != NULL)
		{
			free(get_data()->tokens);
			get_data()->tokens = NULL;
		}
	}
}
