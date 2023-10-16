/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 22:42:52 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checks if a character is allowed in variable name
int	varchar(char c)
{
	return (ft_isalnum(c) == 1 || ft_isalpha(c) == 1 || c == '_');
}

/* takes variable start ($) and returns the pointer
to the first char after its end */
char	*skip_var(char *start)
{
	char	*cur;

	if (ft_strncmp(start, "$?", 2) == 0)
		return (start + 2);
	cur = start;
	cur++;
	while (*cur != '\0' && varchar(*cur))
		cur++;
	return (cur);
}

//given variable start ($) and end, returns its value
static char	*get_value(char *start, char *end, char *exit_stat, char *envp[])
{
	// char	*cur;
	char	*var;
	char	*value;

	if (ft_strncmp(start, "$?", end - start) == 0)
		return (exit_stat);
	var = ft_substr(start + 1, 0, end - start);
	value = getenv1(var, envp);
	free(var);
	return (value);
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

/* substitutes a variable in the string with its value
because it's allocated we need to free it at the end!!!
text[$var]text
text[value]text */
char	*varsubst(char **str, char *start, char *envp[], t_errdata *err)
{
	char	*after_var;
	char	*before_var;
	char	*value;
	int		len;

	after_var = skip_var(start);
	if (start == *str && *after_var == '\0' && !varvalid(start, envp))
		return (after_var);
	value = get_value(start, after_var - 1, err->statstr, envp);
	before_var = ft_substr(*str, 0, start - *str);
	if (value != NULL)
		*str = strjoin3(before_var, value, after_var, err);
	else
		*str = ft_strjoin(before_var, after_var, err);
	len = ft_strlen(before_var);
	free(before_var);
	if (value != NULL)
		return (*str + len + ft_strlen(value));
	else
		return (*str + len);
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
