/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 00:13:58 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/18 00:14:25 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* takes variable start ($) and returns the pointer
to the first char after its end */
char	*skip_var(char *start)
{
	char	*cur;

	if (ft_strncmp(start, "$?", 2) == 0)
		return (start + 2);
	cur = start;
	cur++;
	while ((*cur != '\0' && ft_isalnum(*cur) == 1)
		|| ft_isalpha(*cur) == 1 || *cur == '_')
		cur++;
	return (cur);
}
