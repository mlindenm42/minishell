/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/16 22:46:39 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//for now it frees only a row of a cmd table pointed by the argument
//to be completed later

// free structure and output error
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop)
{
	char	*pref;

	err->stop = stop;
	err->stat = 1;
	if (del != NULL && struc != NULL)
		del(struc);
	perror("minishell");
}

void	custom_err(char *pref, const char *txt)
{
	char *newtxt;
	char *tmp;

	tmp = ft_strjoin(pref, ": ");
	newtxt = ft_strjoin(tmp, txt);
	free(tmp);
	ft_putendl_fd(newtxt, 2);
	free(newtxt);
}
//output error extending its description if needed
void	err_handler(t_errdata *err, char *str, int stop)
{
	char	*pref;
	char	*txt;

	err->stop = stop;
	err->stat = 1;

	if (str != NULL)
	{
		pref = ft_strjoin("minishell: ", (char *)str);
		if (*str == '$')
			custom_err(pref, "ambiguous redirect");
		else
			perror(pref);
		free(pref);
		pref = NULL;
	}
	else
		perror("minishell");
}

void	cmderr(t_errdata *err, void *cmd, int stop)
{
	char	*txt;
	char	*tmp;

	err->stop = stop;
	err->stat = 126;
	tmp = ft_strjoin("minishell: ", (char *)cmd);
	if (ft_strchr(cmd, '/') == NULL)
	{
		custom_err(tmp, "command not found");
		err->stat = 127;
	}
	else
		perror(tmp);
	free(tmp);
	exit(err->stat);
}