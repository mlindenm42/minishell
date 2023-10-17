/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/17 14:07:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//when the string is an invalid variable returns FALSE
//in this case if it's not a in/out the token is ommited
int	valid(char *str, char *envp[])
{
	if (ft_strcmp(str, "$?") != 0 && *str == '$'
		&& (getenv1(str + 1, envp) == NULL)
		&& *skip_var(str) == '\0')
		return (0);
	else
		return (1);
}
