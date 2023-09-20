/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/09/20 14:35:30 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//if a word is nonexisting variable
/* int	varvalid(char *str)
{
	if (ft_strcmp(str, "$?") != 0 && *str == '$' && (getenv(str + 1) == NULL))
		return (FALSE);
	else
		return (TRUE);
} */

//when the string is an invalid variable returns FALSE
//in this case if it's not a in/out the token is ommited
int	varvalid(char *str)
{
	if (ft_strcmp(str, "$?") != 0 && *str == '$' && (getenv(str + 1) == NULL)
		&& *skip_var(str) == '\0')
		return (FALSE);
	else
		return (TRUE);
}