/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:06:03 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 22:30:00 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_stringlist(void)
{
	t_stringlist	*actual;
	t_stringlist	*copy;

	actual = get_data()->slist;
	while (actual != NULL && actual->next != NULL)
	{
		copy = actual;
		actual = actual->next;
		free(copy);
	}
	free(actual);
	get_data()->slist = NULL;
	get_data()->slistend = NULL;
}

void	free_tokenlist(void)
{
	t_tokenlist	*actual;
	t_tokenlist	*copy;

	actual = get_data()->tlist;
	while (actual != NULL && actual->token.type != END)
	{
		copy = actual;
		actual = actual->next;
		free(copy);
	}
	free(actual);
	get_data()->tlist = NULL;
	get_data()->tlistend = NULL;
}

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
	get_data()->tokenslength = 0;
}
