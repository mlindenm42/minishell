/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:45:49 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 21:32:33 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	newvar(char *var, char *val, char *envp[], t_errdata *err)
{
	char	*new_var;

	new_var = NULL;
	new_var = create_elem(&err->gc, sizeof(char),
			ft_strlen(var) + ft_strlen(val) + 2);
	if (new_var != NULL)
	{
		strcpy(new_var, var);
		strcat(new_var, "=");
		strcat(new_var, val);
		envp[get_data()->buffer] = new_var;
	}
	else
	{
		err_handler(err, "variable ", CNT);
		return ;
	}
}

static void	newentry(char *var, char *val, char *envp[], t_errdata *err)
{
	int		i;
	char	*new_entry;

	new_entry = NULL;
	new_entry = create_elem(&err->gc, sizeof(char),
			ft_strlen(var) + ft_strlen(val) + 2);
	if (new_entry != NULL)
	{
		strcpy(new_entry, var);
		strcat(new_entry, "=");
		strcat(new_entry, val);
		i = 0;
		while (envp[i] != NULL)
			i++ ;
		envp[i] = new_entry;
		envp[i + 1] = NULL;
	}
	else
	{
		err_handler(err, "variable ", CNT);
		return ;
	}
}

void	replace_var(char *var, char *val, char *envp[], t_errdata *err)
{
	int		index;
	int		i;

	index = -1;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var))
			== 0 && envp[i][ft_strlen(var)] == '=')
		{
			index = i;
			break ;
		}
		i++;
	}
	if (index != -1)
	{
		get_data()->buffer = index;
		newvar(var, val, envp, err);
	}
	else
		newentry(var, val, envp, err);
}
