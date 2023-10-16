/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:45:47 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 21:31:16 by dgross           ###   ########.fr       */
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
	get_data()->tlistend->token.val = create_pile(&err->gc, sizeof(char), get_slist_length());
	i = 0;
	while (actual->next != NULL)
	{
		get_data()->tlistend->token.val[i++] = actual->character;
		actual = actual->next;
	}
	get_data()->tlistend->token.val[i] = '\0';
	//free_stringlist();
}

void	create_token(int type, const char *val, t_errdata *err)
{
	get_data()->tlistend->token.type = NOTOKEN;
	get_data()->tlistend->token.type = type;
	get_data()->tlistend->token.val = NULL;
	if (type != END)
		get_data()->tlistend->token.val = ft_strdup(val, err);
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
	get_data()->tokens
	= create_pile(&err->gc, sizeof(t_tkn), get_data()->tokenslength);
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

// void	print_tokens(void)
// {
// 	int	i;

// 	i = 0;
// 	while (get_data()->tokens[i].type != END)
// 	{
// 		printf("Token type: %d, Value: %s\n",
// 			get_data()->tokens[i].type, get_data()->tokens[i].val);
// 		i++;
// 	}
// 	printf("Token type: %d\n", get_data()->tokens[i].type);
// }
