/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 10:18:50 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// free structure and output error
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop)
{
	err->stop = stop;
	err->stat = 1;
	if (del != NULL && struc != NULL)
		del(struc);
	perror("minishell");
}

void	custom_err(char *pref, const char *txt, t_errdata *err)
{
	char	*newtxt;
	char	*tmp;

	tmp = ft_strjoin(pref, ": ", err);
	newtxt = ft_strjoin(tmp, txt, err);
	ft_putendl_fd(newtxt, 2);
}

//output error extending its description if needed
void	err_handler(t_errdata *err, char *str, int stop)
{
	char	*pref;

	err->stop = stop;
	err->stat = 1;
	if (str != NULL)
	{
		pref = ft_strjoin("minishell: ", (char *)str, err);
		if (*str == '$')
			custom_err(pref, "ambiguous redirect", err);
		else
			perror(pref);
	}
	else
		perror("minishell");
}

void	cmderr(t_errdata *err, void *cmd, int stop)
{
	char		*tmp;
	struct stat	stat;

	err->stop = stop;
	if (errno == EACCES)
		err->stat = 126;
	else
		err->stat = 127;
	tmp = ft_strjoin("minishell: ", (char *)cmd, err);
	if (lstat(cmd, &stat) == 0 && S_ISDIR(stat.st_mode))
	{
		err->stat = 126;
		custom_err(tmp, "is a directory", err);
	}
	else if (ft_strchr(cmd, '/') == NULL)
	{
		custom_err(tmp, "command not found", err);
	}
	else
		perror(tmp);
	free_data(&err->gc, err->gc.elem);
	exit(err->stat);
}

void	cmderr1(t_errdata *err, void *cmd, char *envp[], int stop)
{
	char			*tmp;
	struct stat		stat;

	err->stop = stop;
	err->stat = 127;
	tmp = ft_strjoin("minishell: ", (char *)cmd, err);
	if (getenv1("PATH", envp) == NULL)
	{
		if (lstat(cmd, &stat) == 0 && S_ISDIR(stat.st_mode))
		{
			err->stat = 126;
			custom_err(tmp, "is a directory", err);
		}
		else
			custom_err(tmp, strerror(2), err);
	}
	else
		custom_err(tmp, "command not found", err);
	free(tmp);
	exit(err->stat);
}
