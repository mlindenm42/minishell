/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/08/19 18:20:19 by mrubina          ###   ########.fr       */
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

char	*extract_path(char *path_str, char *name)
{
	int		access_given;
	char	**path_arr;
	char	*path_cand;
	char	*slash_name;
	int		i;

	i = 0;
	if (name == NULL)
		return (name);
	slash_name = ft_strjoin("/", name);
	path_arr = ft_split(path_str, ':');
	access_given = -1;
	while (path_arr[i] != NULL && access_given == -1)
	{
		path_cand = ft_strjoin(path_arr[i], slash_name);
		access_given = access(path_cand, X_OK);
		i++;
		if (path_cand != NULL && access_given == -1)
			free_str(path_cand);
	}
	free_str(slash_name);
	free_arr(path_arr);
	if (access_given == 0)
		return (path_cand);
	return (name);
}

/* cand_path is "/dir1/dir2/file"
	or "file" */
char	*getpath(char *fpath, char *envp[])
{
	int		n;
	int		i;
	char	*path_str;

	if (access(fpath, X_OK) == 0 && fpath[0] == '.' && fpath[1] == '/')
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
	if (path_str == NULL)
		//error_handler(NULLPATH, path_str, status);
		perror("");
	if ((access(path_str, X_OK) == -1 && errno == EACCES))
		perror("");
		//error_handler(EACCES1, path_str, status);
	if (path_str != NULL && ft_strchr(path_str, '/') == 0)
		perror("");
		//error_handler(NFOUNDEX, path_str, status);
	return (path_str);
}
