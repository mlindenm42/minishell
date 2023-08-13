/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/13 23:36:10 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* structures */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	int		token;
	char	*val;
}	t_token;

typedef struct s_iof
{
	int		io;
	char	*file;
}	t_iof;

typedef struct s_cmdtable
{
	int		pipe;
	char	*cmd;
	char	**args;
	t_iof	*infiles;
	t_iof	*outfiles;
	char	**curr_a;
	t_iof	*curr_i;
	t_iof	*curr_o;
	int		nargs;
	int		nins;
	int		nouts;
}	t_cmdtable;

typedef struct s_data {
	char	*prompt;
	char	*input;
	char	**tokens;
}	t_data;

#endif
