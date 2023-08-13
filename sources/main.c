/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/12 13:57:53 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	//char	*input;
	t_token *tkns;
	t_cmdtable *tbl;

	tkns = lexer();
	tbl = parser(tkns);
	print_table(tbl, 2);

	/* rl_bind_key('\t', rl_complete);
	input = readline("Enter something: ");
	if (input && *input)
	{
		add_history(input);
	}
	printf("You entered: %s\n", input);
	free(input); */
	return (0);
}
