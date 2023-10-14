/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:32:01 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/14 06:45:29 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//for now it frees only a row of a cmd table pointed by the argument
//to be completed later

// free structure and output error
void	errfree(t_errdata *err, void *struc, void (*del)(void *), int stop)
{
	// char	*pref;

	err->stop = stop;
	err->stat = 1;
	if (del != NULL && struc != NULL)
		del(struc);
	perror("minishell");
}

void	setstatstr(t_errdata *err)
{
	if (err->statstr != NULL)
		free(err->statstr);
	err->statstr = ft_itoa(err->stat);
}

void	custom_err(char *pref, const char *txt)
{
	char	*newtxt;
	char	*tmp;

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
	// char	*txt;

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
	// char	*txt;
	char	*tmp;
	struct stat	stat;

	err->stop = stop;
	if (errno == EACCES)
		err->stat = 126;
	else
		err->stat = 127;
	tmp = ft_strjoin("minishell: ", (char *)cmd);
	if (lstat(cmd, &stat) == 0 && S_ISDIR(stat.st_mode))
	{
		err->stat = 126;
		custom_err(tmp, "is a directory");
	}
	else if (ft_strchr(cmd, '/') == NULL)
	{
		custom_err(tmp, "command not found");
	}
	else
		perror(tmp);
	free(tmp);
	exit(err->stat);
}

void	cmderr1(t_errdata *err, void *cmd, char *envp[], int stop)
{
	// char	*txt;
	char	*tmp;
	struct stat	stat;

	err->stop = stop;
	err->stat = 127;
	tmp = ft_strjoin("minishell: ", (char *)cmd);
	if	(getenv1("PATH", envp) == NULL)
	{
		if (lstat(cmd, &stat) == 0 && S_ISDIR(stat.st_mode))
		{
			err->stat = 126;
			custom_err(tmp, "is a directory");
		}
		else
			custom_err(tmp, strerror(2));
	}
	else
		custom_err(tmp, "command not found");
	free(tmp);
	exit(err->stat);
}
