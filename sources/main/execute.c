/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 22:47:22 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(char *envp[], t_errdata *err)
{
	t_cmdtable	*tbl;

	tbl = NULL;
	if (get_data()->tokens->type != END)
	{
		tbl = parser(get_data()->tokens, err);
		expander(tbl, err, envp);
		if (err->stop == CNT)
			executor(tbl, envp, err);
		freecycle(err);
	}
}
