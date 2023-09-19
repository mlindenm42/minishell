/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:36:21 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/16 17:46:45 by mrubina          ###   ########.fr       */
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

	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = -n;
		count = 1;
	}	
	else
		count = 0;
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

/* 
prints positive integer
 */
static void	positive_tostr(int n, int len, int fd)
{
	int	d;

	while (len != 0)
	{
		len--;
		d = power(10, len);
		ft_putchar_fd((char)(n / d + '0'), fd);
		n = n % d;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		number;

	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	len = get_length(n);
	if (n >= 0)
		number = n;
	else
	{
		ft_putchar_fd('-', fd);
		number = -n;
		len--;
	}
	positive_tostr(number, len, fd);
}
