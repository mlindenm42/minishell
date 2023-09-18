/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/18 19:47:38 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//expander edits table according to some rules
static void	replace_filename(int last_ind, t_iof *file, t_errdata *err)
{
	int		j;

	j = 0;
	while (j <= last_ind && isvar(file[j].file))
	{
		if (file[j].file[0] == '$' && ft_strcmp(file[j].file, "$?") != 0)
			file[j].file = getenv(file[j].file + 1);
		else if (ft_strcmp(file[j].file, "$?") == 0)
			file[j].file = err->statstr;
		j++;
	}
}

static void	replace_arg(int last_ind, char **args, t_errdata *err)
{
	int		j;

	j = 0;
	while (j <= last_ind)
	{
		if (ft_strcmp(args[j], "$?") == 0)
			args[j] = err->statstr;
		else if (args[j][0] == '$')
			args[j] = getenv(args[j] + 1);
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
		if (ft_strcmp(tbl[i].cmd, "$?") == 0)
			tbl[i].cmd = err->statstr;
		else if (tbl[i].cmd[0] == '$')
			tbl[i].cmd = getenv(tbl[i].cmd + 1);
		replace_arg(tbl[i].nargs - 1, tbl[i].args, err);
		replace_filename(tbl[i].nins - 1, tbl[i].infiles, err);
		replace_filename(tbl[i].nouts - 1, tbl[i].outfiles, err);
		i++;
	}
}
