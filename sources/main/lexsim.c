/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexsim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/11 22:08:23 by mrubina          ###   ########.fr       */
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
	tkns[2].val = "f1";
	tkns[3].tkn = LT;
	tkns[4].tkn = WORD;
	tkns[4].val = "f2";
	tkns[5].tkn = LT;
	tkns[6].tkn = WORD;
	tkns[6].val = "f1";
	tkns[7].tkn = PIPE;
	tkns[8].tkn = WORD;
	tkns[8].val = "cat";
	tkns[9].tkn = WORD;
	tkns[9].val = "-e";
	tkns[10].tkn = GT;
	tkns[11].tkn = WORD;
	tkns[11].val = "out1";
	tkns[12].tkn = GT;
	tkns[13].tkn = WORD;
	tkns[13].val = "out2";
	tkns[14].tkn = END;
	tkns[14].val = NULL;
	return (tkns);
}
 */
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
	tkns[4].val = "ct";
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
	tkns[12].val = "cat";
	tkns[13].tkn = END;
	tkns[13].val = NULL;
	return (tkns);
} */

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
	tkns[3].tkn = GT;
	tkns[4].tkn = WORD;
	tkns[4].val = "/tertt/t";
	tkns[5].tkn = END;
	tkns[5].val = NULL;
	return (tkns);
} */

/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].tkn = WORD;
	tkns[0].val = "cat";
	tkns[1].tkn = LLT;
	tkns[2].tkn = WORD;
	tkns[2].val = ",";
	tkns[3].tkn = END;
	tkns[3].val = NULL;
	return (tkns);
} */

/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].tkn = WORD;
	tkns[0].val = "cat";
	tkns[1].tkn = LLT;
	tkns[2].tkn = WORD;
	tkns[2].val = "lim";
	tkns[3].tkn = GT;
	tkns[4].tkn = WORD;
	tkns[4].val = "out";
	tkns[5].tkn = PIPE;
	tkns[6].tkn = LLT;
	tkns[7].tkn = WORD;
	tkns[7].val = ".";
	tkns[8].tkn = WORD;
	tkns[8].val = "cat";
	tkns[9].tkn = END;
	tkns[9].val = NULL;
	return (tkns);
} */

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
	// tkns[3].tkn = GT;
	// tkns[4].tkn = WORD;
	// tkns[4].val = "out";
	tkns[5].tkn = PIPE;
	tkns[6].tkn = LT;
	tkns[7].tkn = WORD;
	tkns[7].val = "f2";
	tkns[8].tkn = WORD;
	tkns[8].val = "cat";
	// tkns[7].tkn = WORD;
	// tkns[7].val = "f2";
	tkns[9].tkn = END;
	tkns[9].val = NULL;
	return (tkns);
} */

t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 20;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].tkn = WORD;
	tkns[0].val = "cat";
	tkns[1].tkn = WORD;
	tkns[1].val = "-e";
	tkns[2].tkn = LT;
	tkns[3].tkn = WORD;
	tkns[3].val = "f10";
	// tkns[4].tkn = GT;
	// tkns[5].tkn = WORD;
	// tkns[5].val = "out4";
	tkns[4].tkn = PIPE;
	tkns[5].tkn = WORD;
	tkns[5].val = "cat";
	tkns[6].tkn = WORD;
	tkns[6].val = "-e";
	tkns[7].tkn = GT;
	tkns[8].tkn = WORD;
	tkns[8].val = "out3";
	// tkns[9].tkn = LT;
	// tkns[10].tkn = WORD;
	// tkns[10].val = "f2";
	tkns[9].tkn = PIPE;
	tkns[10].tkn = LT;
	tkns[11].tkn = WORD;
	tkns[11].val = "f2";
	/* tkns[12].tkn = LLT;
	tkns[13].tkn = WORD;
	tkns[13].val = "."; */
	tkns[12].tkn = WORD;
	tkns[12].val = "cat";
	// tkns[13].tkn = GT;
	// tkns[14].tkn = WORD;
	// tkns[14].val = "out3";
	tkns[15].tkn = PIPE;
	tkns[16].tkn = GT;
	tkns[17].tkn = WORD;
	tkns[17].val = "out4";
	tkns[18].tkn = WORD;
	tkns[18].val = "cat";
	tkns[19].tkn = END;
	tkns[19].val = NULL;
	return (tkns);
 }