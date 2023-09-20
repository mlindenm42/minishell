/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexsim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/20 13:50:57 by mrubina          ###   ########.fr       */
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
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = WORD;
	tkns[1].val = "-e";
	tkns[2].type = WORD;
	tkns[2].val = "f1";
	tkns[3].type = LT;
	tkns[4].type = WORD;
	tkns[4].val = "f2";
	tkns[5].type = LT;
	tkns[6].type = WORD;
	tkns[6].val = "f1";
	tkns[7].type = PIPE;
	tkns[8].type = WORD;
	tkns[8].val = "cat";
	tkns[9].type = WORD;
	tkns[9].val = "-e";
	tkns[10].type = GT;
	tkns[11].type = WORD;
	tkns[11].val = "out1";
	tkns[12].type = GT;
	tkns[13].type = WORD;
	tkns[13].val = "out2";
	tkns[14].type = END;
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
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = LT;
	tkns[2].type = WORD;
	tkns[2].val = "f1";
	tkns[3].type = PIPE;
	tkns[4].type = WORD;
	tkns[4].val = "ct";
	tkns[5].type = GT;
	tkns[6].type = WORD;
	tkns[6].val = "out2";
	tkns[7].type = GT;
	tkns[8].type = WORD;
	tkns[8].val = "out3";
	tkns[9].type = PIPE;
	tkns[10].type = GT;
	tkns[11].type = WORD;
	tkns[11].val = "out1";
	tkns[12].type = WORD;
	tkns[12].val = "cat";
	tkns[13].type = END;
	tkns[13].val = NULL;
	return (tkns);
} */

/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = LT;
	tkns[2].type = WORD;
	tkns[2].val = "f1";
	tkns[3].type = GT;
	tkns[4].type = WORD;
	tkns[4].val = "/tertt/t";
	tkns[5].type = END;
	tkns[5].val = NULL;
	return (tkns);
} */

/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = LLT;
	tkns[2].type = WORD;
	tkns[2].val = ",";
	tkns[3].type = END;
	tkns[3].val = NULL;
	return (tkns);
} */

/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = LLT;
	tkns[2].type = WORD;
	tkns[2].val = "lim";
	tkns[3].type = GT;
	tkns[4].type = WORD;
	tkns[4].val = "out";
	tkns[5].type = PIPE;
	tkns[6].type = LLT;
	tkns[7].type = WORD;
	tkns[7].val = ".";
	tkns[8].type = WORD;
	tkns[8].val = "cat";
	tkns[9].type = END;
	tkns[9].val = NULL;
	return (tkns);
} */

/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = LT;
	tkns[2].type = WORD;
	tkns[2].val = "f1";
	// tkns[3].type = GT;
	// tkns[4].type = WORD;
	// tkns[4].val = "out";
	tkns[5].type = PIPE;
	tkns[6].type = LT;
	tkns[7].type = WORD;
	tkns[7].val = "f2";
	tkns[8].type = WORD;
	tkns[8].val = "cat";
	// tkns[7].type = WORD;
	// tkns[7].val = "f2";
	tkns[9].type = END;
	tkns[9].val = NULL;
	return (tkns);
} */

/* t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 22;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = WORD;
	tkns[1].val = "-e";
	tkns[2].type = LT;
	tkns[3].type = WORD;
	tkns[3].val = "f1";
	// tkns[4].type = GT;
	// tkns[5].type = WORD;
	// tkns[5].val = "out4";
	tkns[4].type = PIPE;
	tkns[5].type = WORD;
	tkns[5].val = "cat";
	tkns[6].type = WORD;
	tkns[6].val = "-e";
	// tkns[7].type = GT;
	// tkns[8].type = WORD;
	// tkns[8].val = "out3";
	tkns[9].type = LT;
	tkns[10].type = WORD;
	tkns[10].val = "f20";
	tkns[11].type = PIPE;
	// tkns[10].type = LT;
	// tkns[11].type = WORD;
	// tkns[11].val = "out6";
	// tkns[12].type = LLT;
	// tkns[13].type = WORD;
	// tkns[13].val = ".";
	tkns[12].type = WORD;
	tkns[12].val = "cat";
	// tkns[13].type = GT;
	// tkns[14].type = WORD;
	// tkns[14].val = "out3";
	tkns[15].type = PIPE;
	// tkns[16].type = GT;
	// tkns[17].type = WORD;
	// tkns[17].val = "out4";
	tkns[16].type = WORD;
	tkns[16].val = "wc";
	// tkns[19].type = LLT;
	// tkns[20].type = WORD;
	// tkns[20].val = ",";
	tkns[21].type = END;
	tkns[21].val = NULL;
	return (tkns);
 } */

//awk
/*  t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = WORD;
	tkns[1].val = "f1";
	 tkns[2].type = PIPE;
	tkns[3].type = WORD;
	tkns[3].val = "awk";
	tkns[4].type = WORD;
	tkns[4].val = "\"{count++} END {print count}\"";
	tkns[8].type = END;
	tkns[8].val = NULL;
	return (tkns);
} */

 t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 15;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "cat";
	tkns[1].type = LLT;
	tkns[2].type = WORD;
	tkns[2].val = "$?";
	//tkns[0].val = "\"$USE\"";
	// tkns[1].type = WORD;
	// tkns[1].val = "user name is \"$USER\"";
	// tkns[1].type = WORD;
	// tkns[1].val = "$USER";
	// tkns[1].type = WORD;
	// tkns[1].val = "5";
	// tkns[2].type = WORD;
	// tkns[2].val = "f2";
	//  tkns[2].type = PIPE;
	// tkns[3].type = WORD;
	// tkns[3].val = "awk";
	// tkns[4].type = WORD;
	// tkns[4].val = "\"{count++} END {print count}\"";
	// tkns[2].type = GT;
	// tkns[3].type = WORD;
	// tkns[3].val = "out3";
	tkns[4].type = END;
	tkns[4].val = NULL;
	return (tkns);
}