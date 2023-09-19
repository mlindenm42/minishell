/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:34:22 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/16 17:42:29 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	power(int n, int unsigned p)
{
	int	r;

	r = 1;
	while (p > 0)
	{
		r = r * n;
		p--;
	}
	return (r);
}

static int	get_length(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = -n;
		count = 1;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

/* 
converts positive integer to string
 */
static void	positive_to_str(int n, int len, char *str)
{
	int	d;

	while (len != 0)
	{
		len--;
		d = power(10, len);
		*str = (char)(n / d) + '0';
		n = n % d;
		str++;
	}
	*str = '\0';
}

/* 
allocates memory and converts integer to string
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = get_length(n);
	str = (char *)malloc(len + 1);
	if (str == 0)
		return (0);
	else if (n == -2147483648)
		ft_strlcpy(str, "-2147483648", len + 1);
	else if (n >= 0)
		positive_to_str(n, len, str);
	else
	{
		*str = '-';
		positive_to_str(-n, len - 1, str + 1);
	}
	return (str);
}
