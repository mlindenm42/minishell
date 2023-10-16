/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/16 22:29:30 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//when the string is an invalid variable returns FALSE
//in this case if it's not a in/out the token is ommited
int	varvalid(char *str, char *envp[])
{
	if (ft_strcmp(str, "$?") != 0 && *str == '$' && (getenv1(str + 1, envp) == NULL)
		&& *skip_var(str) == '\0')
		return (0);
	else
		return (1);
}
