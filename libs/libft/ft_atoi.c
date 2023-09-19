/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:17:40 by mrubina           #+#    #+#             */
/*   Updated: 2022/10/18 09:17:40 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
returns 1 if the character should be ommited
 */
static int	isomitted(int c)
{
	if (((c >= 9) && (c <= 13)) || (c == 32))
		return (1);
	else
		return (0);
}

static int	get_sign(int c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			result;
	const char	*abs;
	int			int_sign;

	while (isomitted(*str) == 1)
		str++;
	int_sign = get_sign(*str);
	if (int_sign != 0)
		abs = str + 1;
	else
		abs = str;
	result = 0;
	while (ft_isdigit(*abs) == 1)
	{
		result = result * 10 + *abs - '0';
		abs++;
	}
	if (int_sign == -1)
		result = -result;
	return (result);
}
