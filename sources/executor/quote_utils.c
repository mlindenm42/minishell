/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 08:30:57 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//returns a pointer to the first qote
static char	*firstquote(char *word)
{
	char	*sq;
	char	*dq;

	sq = ft_strchr(word, '\'');
	dq = ft_strchr(word, '"');
	if (sq != NULL && dq != NULL)
	{
		if (sq < dq)
			return (sq);
		else
			return (dq);
	}
	else if (sq != NULL)
		return (sq);
	else if (dq != NULL)
		return (dq);
	else
		return (NULL);
}

// '"$USER"'
static void	exp_quotes(char **word, char *envp[], t_errdata *err)
{
	char	*tmp;

	if (*word != NULL && **word == '\'')
	{
		tmp = ft_strtrim(*word, "\'", err);
		*word = tmp;
	}
	else if (*word != NULL && **word == '"')
	{
		tmp = ft_strtrim(*word, "\"", err);
		*word = tmp;
		varscan(word, envp, err);
	}
	else if (*word != NULL)
		varscan(word, envp, err);
}

static char	*cropjoin2(char *str, char *qpart, int len, t_errdata *err)
{
	char	*part1;
	char	*rtn;

	part1 = ft_substr(str, 0, len);
	rtn = ft_strjoin(part1, qpart, err);
	free(part1);
	return (rtn);
}

static char	*cropjoin3(char *str, char *qpart, char *start, t_errdata *err)
{
	char	*part1;
	char	*rtn;
	char	*part2;

	part1 = ft_substr(str, 0, start - str);
	part2 = ft_strchr(start, *start) + 1;
	rtn = strjoin3(part1, qpart, part2, err);
	free(part1);
	return (rtn);
}

//replaces one pair of quotes
//returns null if no more qoutes left
//first quote should be found from the point where we left (next)
//4 cases: quote part equals word, in the middle
//on the right or on the left
int	replace_q(char **word, char *next, t_errdata *err)
{
	char	*qpart;
	char	*start;
	char	*end;
	char	*str;

	str = *word;
	start = firstquote(next);
	if (start == NULL)
		return (0);
	end = ft_strchr(start, *start);
	qpart = ft_substr(start, 0, end - start + 1);
	exp_quotes(&qpart, err->envp, err);
	if (start == str && *(end + 1) == '\0')
		*word = qpart;
	else if (start != str && *(end + 1) == '\0')
		*word = cropjoin2(str, qpart, start - str, err);
	else if (start == str)
		*word = ft_strjoin(qpart, end + 1, err);
	else if (*(end + 1) != '\0')
		*word = cropjoin3(str, qpart, start, err);
	return (ft_strlen(next) - (end - start) - 1);
}
