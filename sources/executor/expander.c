/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/20 13:46:53 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//expander edits table according to some rules
static void	replace_filename(int last_ind, t_iof *file, t_errdata *err)
{
	int		j;

	j = 0;
	while (j <= last_ind)
	{
		if (file[j].io != LLT)
			expand_word(&file[j].file, err->statstr);
		j++;
	}
}

static void	replace_arg(int last_ind, char **args, t_errdata *err)
{
	int		j;

	j = 0;
	while (j <= last_ind)
	{
		expand_word(&args[j], err->statstr);
		j++;
	}
}

void	expander(t_cmdtable *tbl, t_errdata *err)
{
	int		i;

	i = 0;
	setstatstr(err);
	while (i <= tbl->nrows - 1)
	{
		expand_word(&tbl[i].cmd, err->statstr);
		replace_arg(tbl[i].nargs - 1, tbl[i].args, err);
		replace_filename(tbl[i].nins - 1, tbl[i].infiles, err);
		replace_filename(tbl[i].nouts - 1, tbl[i].outfiles, err);
		i++;
	}
}

//if single quotes remove them
//if double quotes expand variables and remove quotes
//if no quotes expand vars
void	expand_word(char **word, char *exit_stat)
{
	char	*tmp;

	if (**word == '\'')
		*word = ft_strtrim(*word, "\'");
	else if (**word == '"')
	{
		tmp = ft_strtrim(*word, "\"");
		*word = tmp;
		varscan(word, exit_stat);
		free(tmp);
	}
	else
		varscan(word, exit_stat);
}