/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:45:47 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 10:23:51 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_slist_length(void)
{
	t_stringlist	*actual;
	int				counter;

	actual = get_data()->slist;
	counter = 1;
	while (actual->next != NULL)
	{
		counter++;
		actual = actual->next;
	}
	return (counter);
}

void	create_tokenword(int type, t_errdata *err)
{
	t_stringlist	*actual;
	int				i;

	get_data()->tlistend->token.type = NOTOKEN;
	get_data()->tlistend->token.type = type;
	actual = get_data()->slist;
	get_data()->tlistend->token.val = NULL;
	(get_data()->tlistend->token.val
			= create_elem(&err->gc, sizeof(char), get_slist_length()));
	i = 0;
	while (actual->next != NULL)
	{
		get_data()->tlistend->token.val[i++] = actual->character;
		actual = actual->next;
	}
	get_data()->tlistend->token.val[i] = '\0';
}

void	create_token(int type, const char *val, t_errdata *err)
{
	get_data()->tlistend->token.type = NOTOKEN;
	get_data()->tlistend->token.type = type;
	get_data()->tlistend->token.val = NULL;
	if (type != END)
		(get_data()->tlistend->token.val = ft_strdup(val, err));
}

void	tokenlist_to_array(t_errdata *err)
{
	t_tokenlist	*actual;
	int			i;

	get_data()->tokenslength = 0;
	actual = get_data()->tlist;
	while (actual != NULL)
	{
		get_data()->tokenslength++;
		actual = actual->next;
	}
	get_data()->tokens = NULL;
	(get_data()->tokens
			= create_elem(&err->gc, sizeof(t_tkn), get_data()->tokenslength));
	i = 0;
	actual = get_data()->tlist;
	while (i < get_data()->tokenslength)
	{
		get_data()->tokens[i].type = actual->token.type;
		get_data()->tokens[i].val = actual->token.val;
		actual = actual->next;
		i++;
	}
}
