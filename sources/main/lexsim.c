/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexsim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/24 00:09:31 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//dummy function: lexer simulator
//simulates: cat -e f1 | grep line > out1 > out2
/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].tkn = WORD;
	tkns[0].val = "cat";
	tkns[1].tkn = WORD;
	tkns[1].val = "-e";
	tkns[2].tkn = WORD;
	tkns[2].val = "f5";
	tkns[3].tkn = LT;
	tkns[4].tkn = WORD;
	tkns[4].val = "f6";
	tkns[5].tkn = LT;
	tkns[6].tkn = WORD;
	tkns[6].val = "f1";
	tkns[7].tkn = PIPE;
	tkns[8].tkn = WORD;
	tkns[8].val = "wc";
	tkns[9].tkn = WORD;
	tkns[9].val = "-l";
	tkns[10].tkn = GT;
	tkns[11].tkn = WORD;
	tkns[11].val = "out1";
	tkns[12].tkn = GT;
	tkns[13].tkn = WORD;
	tkns[13].val = "out2";
	tkns[14].tkn = END;
	tkns[14].val = NULL;
	return (tkns);
} */

//
/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].tkn = WORD;
	tkns[0].val = "cat";
	tkns[1].tkn = LT;
	tkns[2].tkn = WORD;
	tkns[2].val = "f1";
	tkns[3].tkn = PIPE;
	tkns[4].tkn = WORD;
	tkns[4].val = "cat";
	tkns[5].tkn = GT;
	tkns[6].tkn = WORD;
	tkns[6].val = "out2";
	tkns[7].tkn = GT;
	tkns[8].tkn = WORD;
	tkns[8].val = "out3";
	tkns[9].tkn = PIPE;
	tkns[10].tkn = GT;
	tkns[11].tkn = WORD;
	tkns[11].val = "out1";
	tkns[12].tkn = WORD;
	tkns[12].val = "wc";
	tkns[13].tkn = END;
	tkns[13].val = NULL;
	return (tkns);
} */

t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].tkn = WORD;
	tkns[0].val = "cat";
	tkns[1].tkn = LT;
	tkns[2].tkn = WORD;
	tkns[2].val = "f1";
	tkns[3].tkn = END;
	tkns[3].val = NULL;
	return (tkns);
}
