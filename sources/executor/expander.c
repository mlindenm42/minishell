/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/14 23:49:59 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//expander edits table according to some rules
static void	replace_filename(int last_ind, t_iof *file, t_errdata *err, char *envp[])
{
	int		j;

	j = 0;
	while (j <= last_ind)
	{
		if (file[j].io != LLT)
			expand_word(&file[j].file, err->statstr, envp);
		j++;
	}
}

static void	replace_arg(int last_ind, char **args, t_errdata *err, char *envp[])
{
	int		j;

	j = 0;
	while (j <= last_ind)
	{
		expand_word(&args[j], err->statstr, envp);
		//printf("arg in exp %p\n", args[1]);
		j++;
	}
}

void	expander(t_cmdtable *tbl, t_errdata *err, char *envp[])
{
	int		i;

	i = 0;
	//dprintf(2, "args in exp err %s\n", err->tbl->args[0]);
	setstatstr(err);
	//dprintf(2, "args in exp err %s\n", err->tbl->args[0]);
	//dprintf(2, "args in exp %s\n", tbl->args[0]);
	while (i <= tbl->nrows - 1)
	{
		expand_word(&tbl[i].cmd, err->statstr, envp);
		replace_arg(tbl[i].nargs - 1, tbl[i].args, err, envp);
		replace_filename(tbl[i].nins - 1, tbl[i].infiles, err, envp);
		replace_filename(tbl[i].nouts - 1, tbl[i].outfiles, err, envp);
		i++;
	}
}

//if single quotes remove them
//if double quotes expand variables and remove quotes
//if no quotes expand vars
void	expand_word(char **word, char *exit_stat, char *envp[])
{
	char	*tmp;

	//free(*word);
	//exit(0);
	if (*word != NULL && **word == '\'')
		*word = ft_strtrim(*word, "\'");
	else if (*word != NULL && **word == '"')
	{
		tmp = ft_strtrim(*word, "\"");
		*word = tmp;
		varscan(word, exit_stat, envp);
		//free(tmp);
	}
	else if (*word != NULL)
		varscan(word, exit_stat, envp);
}
