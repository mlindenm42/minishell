/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/28 19:32:26 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* structures */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_tkn
{
	int		type;
	char	*val;
}	t_tkn;

typedef struct s_iof
{
	int		io;
	char	*file;
}	t_iof;

typedef struct s_errdata
{
	int		stop;
	int		stat;
	char	*statstr;
	char	**envp_loc;
	char	*envmem_end;
}	t_errdata;

typedef struct s_cmdtable
{
	int			pipeid;
	char		*cmd;
	char		**args;
	t_iof		*infiles;
	t_iof		*outfiles;
	char		**curr_a;
	t_iof		*curr_i;
	t_iof		*curr_o;
	int			nrows;
	int			nargs;
	int			nins;
	int			nouts;
	int			eflag;
	t_errdata	*err;
}	t_cmdtable;

typedef struct s_data {
	char	*prompt;
	char	*input;
	t_tkn	*tokens;
}	t_data;

#endif