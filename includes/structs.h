/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:35:51 by mrubina           #+#    #+#             */
<<<<<<<<< Temporary merge branch 1
/*   Updated: 2023/10/15 20:11:41 by mlindenm         ###   ########.fr       */
=========
/*   Updated: 2023/10/15 22:15:30 by mrubina          ###   ########.fr       */
>>>>>>>>> Temporary merge branch 2
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

typedef struct s_tokenlist
{
	struct s_tokenlist	*next;
	t_tkn				token;
}	t_tokenlist;

typedef struct s_stringlist
{
	struct s_stringlist	*next;
	char				character;
}	t_stringlist;

typedef struct s_iof
{
	int		io;
	char	*file;
}	t_iof;

typedef struct s_exedata
{
	int		infd;
	int		outfd;
	int		intmpfd;
	int		outtmpfd;
	int		status;
	int		pbreak;
	pid_t	*id;
	char	**path;
	int	nrows;
}	t_exedata;

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
	int			path_flag;
}	t_cmdtable;

typedef struct s_errdata
{
	int		stop;
	int		stat;
	char	*statstr;
	t_cmdtable	*tbl;
	t_exedata	*edata;
	char **envp;
}	t_errdata;

typedef struct s_data {
	char			*prompt;
	char			*input;
	t_tkn			*tokens;
	int				tokenslength;
	t_stringlist	*slist;
	t_stringlist	*slistend;
	t_tokenlist		*tlist;
	t_tokenlist		*tlistend;
}	t_data;

#endif
