/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexsim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/28 16:39:41 by mrubina          ###   ########.fr       */
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
	tkns[0].val = "unset";
	// tkns[1].type = LLT;
	// tkns[2].type = WORD;
	// tkns[2].val = "$?";
	//tkns[0].val = "\"$USE\"";
	tkns[1].type = WORD;
	tkns[1].val = "HOME";
	// tkns[1].type = WORD;
	// tkns[1].val = "USER";
	// tkns[1].type = WORD;
	// tkns[1].val = "f1";
	// tkns[1].type = WORD;
	// tkns[1].val = "var2=ireplacedit";
	// tkns[2].type = WORD;
	// tkns[2].val = "var1";
	// tkns[3].type = WORD;
	// tkns[3].val = "va5";
	// tkns[4].type = WORD;
	// tkns[4].val = "USER";
	// tkns[5].type = WORD;
	// tkns[5].val = "OLDPWD";
	// tkns[1].type = PIPE;
	// tkns[2].type = WORD;
	// tkns[2].val = "wc";
	// tkns[4].type = WORD;
	// tkns[4].val = "\"{count++} END {print count}\"";
	// tkns[2].type = GT;
	// tkns[3].type = WORD;
	// tkns[3].val = "out3";
	tkns[6].type = END;
	tkns[6].val = NULL;
	return (tkns);
}

//export test
/*  t_tkn *lexer()
{
	t_tkn *tkns;
	int size;

	size = 52;
	tkns = malloc(size * sizeof(t_tkn));
	tkns[0].type = WORD;
	tkns[0].val = "export";
	// tkns[1].type = LLT;
	// tkns[2].type = WORD;
	// tkns[2].val = "$?";
	//tkns[0].val = "\"$USE\"";
	tkns[1].type = WORD;
	tkns[1].val = "a1=1";
	tkns[2].type = WORD;
	tkns[2].val = "a2=1";
	tkns[3].type = WORD;
	tkns[3].val = "a3=1";
	tkns[4].type = WORD;
	tkns[4].val = "a4=1";
	tkns[5].type = WORD;
	tkns[5].val = "a5=1";
	tkns[6].type = WORD;
	tkns[6].val = "a6=1";
	tkns[7].type = WORD;
	tkns[7].val = "a7=1";
	tkns[8].type = WORD;
	tkns[8].val = "a8=1";
	tkns[9].type = WORD;
	tkns[9].val = "a9=1";
	tkns[10].type = WORD;
	tkns[10].val = "a10=1";
	tkns[11].type = WORD;
	tkns[11].val = "a11=1";
	tkns[12].type = WORD;
	tkns[12].val = "a12=1";
	tkns[13].type = WORD;
	tkns[13].val = "a13=1";
	tkns[14].type = WORD;
	tkns[14].val = "a14=1";
	tkns[15].type = WORD;
	tkns[15].val = "a15=1";
	tkns[16].type = WORD;
	tkns[16].val = "a16=1";
	tkns[17].type = WORD;
	tkns[17].val = "a17=1";
	tkns[18].type = WORD;
	tkns[18].val = "a18=1rer";
	tkns[19].type = WORD;
	tkns[19].val = "a19=1";
	tkns[20].type = WORD;
	tkns[20].val = "a20=1";
	tkns[21].type = WORD;
	tkns[21].val = "a21=1";
	tkns[22].type = WORD;
	tkns[22].val = "a22=1";
	tkns[23].type = WORD;
	tkns[23].val = "a23=2";
	tkns[24].type = WORD;
	tkns[24].val = "a24=2";
	tkns[25].type = WORD;
	tkns[25].val = "a25=2";
	tkns[26].type = WORD;
	tkns[26].val = "a26=2";
	tkns[27].type = WORD;
	tkns[27].val = "a27=2";
	tkns[28].type = WORD;
	tkns[28].val = "a28=2rer";
	tkns[29].type = WORD;
	tkns[29].val = "a29=2";
	tkns[30].type = WORD;
	tkns[30].val = "a30=1";
	tkns[31].type = WORD;
	tkns[31].val = "a31=1";
	tkns[32].type = WORD;
	tkns[32].val = "a32=1";
	tkns[33].type = WORD;
	tkns[33].val = "a33=1";
	tkns[34].type = WORD;
	tkns[34].val = "a34=1";
	tkns[35].type = WORD;
	tkns[35].val = "a35=1";
	tkns[36].type = WORD;
	tkns[36].val = "a36=1";
	tkns[37].type = WORD;
	tkns[37].val = "a37=1";
	tkns[38].type = WORD;
	tkns[38].val = "a38=1";
	tkns[39].type = WORD;
	tkns[39].val = "a39=1";
	tkns[40].type = WORD;
	tkns[40].val = "a40=1";
	tkns[41].type = WORD;
	tkns[41].val = "a41=1";
	tkns[42].type = WORD;
	tkns[42].val = "a42=23231";
	tkns[43].type = WORD;
	tkns[43].val = "a43=1";
	tkns[44].type = WORD;
	tkns[44].val = "a44=1";
	tkns[45].type = WORD;
	tkns[45].val = "a45=1";
	tkns[46].type = WORD;
	tkns[46].val = "a46=1";
	tkns[47].type = WORD;
	tkns[47].val = "a47=1";
	tkns[48].type = WORD;
	tkns[48].val = "a48=1";
	tkns[49].type = WORD;
	tkns[49].val = "a49=1";
	tkns[50].type = WORD;
	tkns[50].val = "a50=1";
	tkns[51].type = END;
	tkns[51].val = NULL;
	return (tkns);
} */