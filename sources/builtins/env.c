/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 00:01:04 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//prints all env variables excluding no value format
void	printenv(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
}

//returns pointer to the end of the last used character of the
//allocated memory
//we use memory after it for created variables
char *getenvmem_end(char *envp[])
{
	char *end;

	while (*envp != NULL)
		envp++;
	end = *(envp - 1);
	//printf("last var unst %s\n", end);
	while (*end != '\0')
		end++;
	return (end);
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

void	shiftenvs(char *var, char *envp[], int shift, char *end)
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

//sets pointers for env variables to their memory respectively
//after changes in that memory
void	shiftenv(char *var, char *envp[], int shift, char *end)
{
	int	i;

	i = 0;
	while (envp[i] != var)
		i++;
	i++;
	while (envp[i + 1] != NULL)
	{
		if (envp[i + 1] >= var && envp[i + 1] <= end)
			envp[i] = envp[i + 1] + shift;
		else
			envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}



/*
replaces or deletes variable

 */
//printf("next %s\n", getstrend(start) + 1);
	//getstrend(start)//old end
	//start + len + 1//new end
	//start + len + 1 - getstrend(start);//diff

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


void unset_var(char *vname, char *envp[])
{
	char *start;
	char *dst;
	char *end;
	char	*env_end;

	start = getvarstart(vname, envp, varlen(vname));
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

// //checks if env has OLDPWD
// int	hasoldpwd(char *envp[])
// {
// 	int	i;
// 	int	oldpwd;

// 	i = 0;
// 	oldpwd = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
// 		{
// 			oldpwd = 1;
// 		}
// 		i++;
// 	}
// 	return (oldpwd);
// }

char	*getenv1(char *var, char *envp[])
{
	char	*value;
	int		i;
	int		len;

	value = getenv(var);
	if (value != NULL)
		return (value);
	i = 0;
	while (envp[i] != NULL)
	{
		len = ft_strlen(var);
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			value = ft_strchr(envp[i], '=') + 1;
		i++;
	}
	return (value);
}


//edits or adds OLDPWD as in bash
//changes SHLVL
//malloc!!!
void	set_loc_env(char *envp[], t_errdata *err)
{
	// int	n;
	// char *undsc;
	char	*shlvl;
	//add pwd!!!
	// n = arr_len(envp);
	if (hasoldpwd(envp) == 1)
		replace_var("OLDPWD", NULL, envp);
	else
		envappend("OLDPWD", envp);
	shlvl = ft_itoa((ft_atoi(getenv1("SHLVL", envp)) + 1), err);
	replace_var("SHLVL", shlvl, envp);
}
