/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/18 00:14:43 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//given variable start ($) and end, returns its value
static char	*get_value(char *start, char *end, char *exit_stat, t_errdata *err)
{
	char	*var;
	char	*value;

	if (ft_strncmp(start, "$?", end - start) == 0)
		return (exit_stat);
	var = ft_substr(start + 1, 0, end - start, err);
	value = getenv1(var, err->envp);
	return (value);
}

/* substitutes a variable in the string with its value
because it's allocated we need to free it at the end!!!
text[$var]text
text[value]text */
static char	*varsubst(char **str, char *start, char *envp[], t_errdata *err)
{
	char	*after_var;
	char	*before_var;
	char	*value;
	int		len;

	after_var = skip_var(start);
	if (start == *str && *after_var == '\0' && !valid(start, envp))
		return (after_var);
	value = get_value(start, after_var - 1, err->statstr, err);
	before_var = ft_substr(*str, 0, start - *str, err);
	if (value != NULL)
		*str = strjoin3(before_var, value, after_var, err);
	else
		*str = ft_strjoin(before_var, after_var, err);
	len = ft_strlen(before_var);
	if (value != NULL)
		return (*str + len + ft_strlen(value));
	else
		return (*str + len);
}

//joins 3 strings
char	*strjoin3(char *str1, char *str2, char *str3, t_errdata *err)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(str1, str2, err);
	result = ft_strjoin(tmp, str3, err);
	return (result);
}

//scanning a string for vars and substituting if necessary
void	varscan(char **word, char *envp[], t_errdata *err)
{
	char	*cur;

	cur = *word;
	while (cur != NULL && *cur != '\0')
	{
		cur = ft_strchr(cur, '$');
		if (cur != NULL)
			cur = varsubst(word, cur, envp, err);
	}
}

//scanning a string for vars and substituting if necessary
//skipping parts inside quotes
void	varscannq(char **word, char *envp[], t_errdata *err)
{
	char	*cur;

	cur = *word;
	while (cur != NULL && *cur != '\0')
	{
		if (*cur != '"' && *cur != '\'')
		{
			if (*cur == '$')
				cur = varsubst(word, cur, envp, err);
			else
				cur++;
		}
		if (*cur == '\'')
			cur = ft_strchr(cur + 1, '\'') + 1;
		if (*cur == '"')
			cur = ft_strchr(cur + 1, '"') + 1;
	}
}
