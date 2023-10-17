/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 06:14:54 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 12:43:44 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//if a variable exists returns the pointer
//to its start
//vname only first l chars!!!
static char	*var(char *vname, char *envp[], int l)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], vname, l) == 0
			&& (envp[i][l] == '=' || envp[i][l] == '\0' ))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static int	vlen(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	shiftenvs(char *var, char *envp[], int shift, char *end)
{
	int	i;

	i = 0;
	while (envp[i] != var)
		i++;
	i++;
	while (envp[i] != NULL)
	{
		if (envp[i] >= var && envp[i] <= end)
			envp[i] = envp[i] + shift;
		i++;
	}
}

//if a variable exists returns the pointer
//to its start
//vname only first l chars!!!
char *getvarstart(char *vname, char *envp[], int l)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], vname, l) == 0
			&& (envp[i][l] == '=' || envp[i][l] == '\0' ))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

//gets length of a variable from an argument)
//var1=test var2
int 	varlen(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
	{
		i++;
	}
	return (i);
}

void replace_var(char *vname, char *val, char *envp[])
{
	int	len;
	char *start;
	char *dst;
	char *end;
	char	*env_end;
	int	n;

	len = varlen(vname); //vname malloced needed only for length
	start = getvarstart(vname, envp, len);//p0
	end = start + ft_strlen(start);// end of old var start of after end + 1  p2
	if (val != NULL)
		len = len + ft_strlen(val) + 1;//new len
	dst = start + len + 1;//place where after is shifted
	if (ft_strchr(start, '=') == NULL)
	 	*end = '=';
	if (val == NULL)
		*(dst - 1) = '\0';
	env_end = getenvmem_end(envp);
	if (env_end != end)
		ft_memmove(dst, end + 1, env_end - end);
	else
	{
		n = arr_len(envp);
		envp[n - 2] = start;
	}
	if (dst - end - 1 < 0)
		ft_bzero(env_end + (dst - end) - 1, end + 1 - dst);
	if (val != NULL)
		ft_strlcpy(start + varlen(vname) + 1, val, ft_strlen(val) + 1);
	if (env_end != end)
		shiftenvs(start, envp, len - (end - start), env_end);
}

// void	replace_var(char *v, char *val, char *e[])
// {
// 	int		len;
// 	char	*dst;
// 	char	*end;
// 	char	*env_end;

// 	len = 0;
// 	end = var(v, e, vlen(v)) + ft_strlen(var(v, e, vlen(v)));
// 	if (val != NULL)
// 		len = vlen(v) + ft_strlen(val) + 1;
// 	dst = var(v, e, vlen(v)) + len + 1;
// 	if (ft_strchr(var(v, e, vlen(v)), '=') == NULL)
// 		*end = '=';
// 	if (val == NULL)
// 		*(dst - 1) = '\0';
// 	env_end = getenvmem_end(e);
// 	if (env_end != end)
// 		ft_memmove(dst, end + 1, env_end - end);
// 	else
// 		e[arr_len(e) - 2] = var(v, e, vlen(v));
// 	if (dst - end - 1 < 0)
// 		ft_bzero(env_end + (dst - end) - 1, end + 1 - dst);
// 	if (val != NULL)
// 		ft_strlcpy(var(v, e, vlen(v)) + vlen(v) + 1, val, ft_strlen(val) + 1);
// 	if (env_end != end)
// 		shiftenvs(var(v, e, vlen(v)), e,
// 			len - (end - var(v, e, vlen(v))), env_end);
// }

void	unset_var(char *vname, char *envp[])
{
	char	*start;
	char	*dst;
	char	*end;
	char	*env_end;

	start = var(vname, envp, vlen(vname));
	end = start + ft_strlen(start);
	dst = start;
	env_end = getenvmem_end(envp);
	if (env_end != end)
		ft_memmove(dst, end + 1, env_end - end);
	ft_bzero(env_end + (dst - end) - 1, end + 1 - dst);
	if (env_end == end)
		envp[arr_len(envp) - 2] = NULL;
	else
		shiftenv(start, envp, start - end - 1, env_end);
}
