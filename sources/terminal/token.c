/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:45:47 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 00:16:51 by mlindenm         ###   ########.fr       */
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

void	create_tokenword(int type)
{
	t_stringlist	*actual;
	int				i;

	get_data()->tlistend->token.type = NOTOKEN;
	get_data()->tlistend->token.type = type;
	actual = get_data()->slist;
	get_data()->tlistend->token.val = NULL;
	get_data()->tlistend->token.val
	= (char *)malloc(get_slist_length() * sizeof(char));
	i = 0;
	while (actual->next != NULL)
	{
		get_data()->tlistend->token.val[i++] = actual->character;
		actual = actual->next;
	}
	get_data()->tlistend->token.val[i] = '\0';
	free_stringlist();
}

void	create_token(int type, const char *val)
{
	get_data()->tlistend->token.type = NOTOKEN;
	get_data()->tlistend->token.type = type;
	get_data()->tlistend->token.val = NULL;
	if (type != END)
		get_data()->tlistend->token.val = ft_strdup(val);
}

void	tokenlist_to_array(void)
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
	= (t_tkn *) malloc(get_data()->tokenslength * sizeof(t_tkn));
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
