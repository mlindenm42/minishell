/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/19 17:43:18 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expandwrd(char **word)
{
	//if single quotes remove them
	//if double quotes expand variables and remove quotes
	//if no quotes expand vars
}

//checks if a character is allowed in variable name
int	varchar(char c)
{
	return (ft_isalnum(c) == 1 || ft_isalpha(c) == 1 || c == '_');
}


//takes variable start ($) and returns the pointer to the first char after its end
char *skip_var(char *start)
{
	char	*cur;

	cur = start;
	cur++;
	while (*cur != '\0' && varchar(*cur))
		cur++;
	return (cur);
}

//given variable start ($) and  end returns its value
char *get_value(char *start, char *end, char *exit_stat)
{
	char	*cur;
	char	*var;
	char	*value;

	if (ft_strcmp(start, "$?") == 0)
		return (exit_stat);
	var = ft_substr(start + 1, 0, end - start + 1); //allocated
	value = getenv(var);
	free(var);
	return (value);
}

char	*strjoin3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(str1, str2);
	result = ft_strjoin(tmp, str3);
	free(tmp);
	return (result);
}
//substitutes a variable in the string with its value
//because it's allocated we need to free it at the end!!!
char	*varsubst(char **str, char *start, char *exit_stat)
{
	char	*cur;
	char	*before_var;
	char	*value;

	cur = *skip_var(start);
	value = get_value(start, cur - 1, exit_stat);
	before_var = ft_substr(*str, 0, start - *str);//allocated
	if (value != NULL)
		*str = strjoin3(before_var, value, cur);
	else
		*str = ft_strjoin(before_var, cur);
	free(before_var);
	dprintf(2, "new word %s\n", *str);
	return (before_var);
}

//scanning a string for vars and substituting if necessary
void	varscan(char **word)
{
	char	*cur;
	int		i;

	cur = *word;
	while (*cur != '\0')
	{
		cur = ft_strchr(cur, '$');
		if (cur != NULL)
			cur = varsubst(word, cur);
		//find var end
		//subst or ignore
	}
}
