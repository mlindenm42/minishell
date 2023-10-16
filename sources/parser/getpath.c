/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:37:30 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 21:44:54 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* "/dir1/dir2:/dir3/dir4:..." - path_str
	"dir3/dir4/file" - path */
// gets path for a command
//if path not found returns command
char	*extract_path(char *path_str, char *cmd, t_errdata *err)
{
	int		access_given;
	char	**path_arr;
	char	*path_cand;
	char	*slash_cmd;
	int		i;

	i = 0;
	//dprintf(2, "cmd%s\n", cmd);
	slash_cmd = ft_strjoin("/", cmd, err);
	//dprintf(2, "s cmd%s\n", slash_cmd);
	//dprintf(2, "cmd%p\n", cmd);
	path_arr = ft_split(path_str, ':');
	access_given = -1;
	while (path_arr[i] != NULL && access_given == -1)
	{
		path_cand = ft_strjoin(path_arr[i], slash_cmd, err);
		access_given = access(path_cand, X_OK);
		i++;
		if (path_cand != NULL && access_given == -1)
			free_str(&path_cand);
	}
	free_str(&slash_cmd);
	free_arr(path_arr);
	if (access_given == 0)
		return (path_cand);
	if (path_cand != NULL)
		free_str(&path_cand);
	return (ft_strdup(cmd));
}

/* cand_path is "/dir1/dir2/file"
	or "file"
	1) check if we need ./ before command
	2) find path variable
	3) extract needed path from env (special case of null env)
	*/
char	*getpath(char *fpath, char *envp[], t_errdata *err)
{
	int		n;
	int		i;
	char	*path_str;

	if (isbuiltin(fpath) || ft_strchr(fpath, '/') != NULL)
		return (ft_strdup(fpath));
	if (fpath[0] == '\0')
		return (ft_strdup(fpath));
	n = 1;
	i = 0;
	while (envp && envp[i] != NULL && n != 0)
	{
		n = ft_strncmp(envp[i], "PATH=", 5);
		if (n != 0)
			i++;
	}
	if (envp && envp[i] != NULL && n == 0)
		path_str = extract_path(&((envp[i])[5]), fpath, err);
	else if (access(fpath, X_OK) == 0)
		path_str = ft_strdup(fpath);
	else
		free_str(&path_str);
	return (path_str);
}
