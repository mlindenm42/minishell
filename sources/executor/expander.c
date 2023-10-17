/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 05:51:44 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//expander edits table according to some rules
static void	replace_filename(int last_ind, t_iof *file,
t_errdata *err, char *envp[])
{
	int		j;

	j = 0;
	while (j <= last_ind)
	{
		if (file[j].io != LLT)
			expand_word(&file[j].file, envp, err);
		j++;
	}
}

static void	replace_arg(int last_ind, char **args, t_errdata *err, char *envp[])
{
	int		j;

	j = 0;
	while (j <= last_ind)
	{
		expand_word(&args[j], envp, err);
		j++;
	}
}

void	expander(t_cmdtable *tbl, t_errdata *err, char *envp[])
{
	int		i;

	i = 0;
	setstatstr(err);
	while (i <= tbl->nrows - 1)
	{
		expand_word(&tbl[i].cmd, envp, err);
		replace_arg(tbl[i].nargs - 1, tbl[i].args, err, envp);
		replace_filename(tbl[i].nins - 1, tbl[i].infiles, err, envp);
		replace_filename(tbl[i].nouts - 1, tbl[i].outfiles, err, envp);
		i++;
	}
}

//offset from the end of the string to the point
//where we should continue scanning
//'"$USER"'test'jj'
void	expand_word(char **word, char *envp[], t_errdata *err)
{
	int offset;
	char *str_end;
	char *next;

	str_end = *word + ft_strlen(*word) - 1;
	offset = ft_strlen(*word) - 1;
	next = *word;
	while (offset > 0)
	{
		offset = replace_q(word, next, err);//malloc
		if (offset == 0)
			break;
		str_end = *word + ft_strlen(*word) - 1;
		next = str_end - offset + 1;
	}
}
