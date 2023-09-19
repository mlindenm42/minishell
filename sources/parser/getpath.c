/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/03 21:08:50 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* "/dir1/dir2:/dir3/dir4:..." - path_str
	"dir3/dir4/file" - path */

void	free_arr(char **arr)
{
	char	**i;

	if (arr != NULL)
	{
		i = arr;
		while (*i != NULL)
		{
			free(*i);
			i++;
		}
		free(arr);
	}
}

void	free_str(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
}

// gets path for a command
//if path not found returns command
char	*extract_path(char *path_str, char *cmd)
{
	int		access_given;
	char	**path_arr;
	char	*path_cand;
	char	*slash_cmd;
	int		i;

	i = 0;
	slash_cmd = ft_strjoin("/", cmd);
	path_arr = ft_split(path_str, ':');
	access_given = -1;
	while (path_arr[i] != NULL && access_given == -1)
	{
		path_cand = ft_strjoin(path_arr[i], slash_cmd);
		access_given = access(path_cand, X_OK);
		i++;
		if (path_cand != NULL && access_given == -1)
			free_str(path_cand);
	}
	free_str(slash_cmd);
	free_arr(path_arr);
	if (access_given == 0)
		return (path_cand);
	return (cmd);
}

/* cand_path is "/dir1/dir2/file"
	or "file"
	1) check if we need ./ before command
	2) find path variable
	3) extract needed path from env (special case of null env)
	*/
char	*getpath(char *fpath, char *envp[])
{
	int		n;
	int		i;
	char	*path_str;

	if (fpath[0] == '.' && fpath[1] == '/')
		return (fpath);
	if (fpath[0] == '\0')
		return (fpath);
	n = 1;
	i = 0;
	while (envp && envp[i] != NULL && n != 0)
	{
		n = ft_strncmp(envp[i], "PATH=", 5);
		if (n != 0)
			i++;
	}
	if (envp && envp[i] != NULL && n == 0)
		path_str = extract_path(&((envp[i])[5]), fpath);
	else
		path_str = extract_path(NULL, fpath);
	return (path_str);
}
