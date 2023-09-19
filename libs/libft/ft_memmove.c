/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:09:30 by mrubina           #+#    #+#             */
/*   Updated: 2022/12/16 17:55:53 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
copies to buffer, returns size copied to buffer and moves 
source current position accordingly
*/
static size_t	to_buff(char *buff, const char **src, size_t b_max, size_t rm)
{
	size_t	size;

	if (b_max <= rm)
		size = b_max;
	else
		size = rm;
	ft_memcpy(buff, *src, size);
	*src = *src + size - 1;
	return (size);
}

static void	from_buff(char **dst, char *buffer, size_t size)
{
	ft_memcpy(*dst, buffer, size);
	*dst = *dst + size - 1;
}

char	*buff_sw(char buffs[2][1000], char *b)
{
	if ((b == &buffs[0][0]) || (b == 0))
		return (&buffs[1][0]);
	else if (b == &buffs[1][0])
		return (&buffs[0][0]);
	else
		return (0);
}

/*
copies final part of the string from buffers
*/
static void	final_step(char *b, char bs[2][1000], size_t f, char **dst)
{
	size_t	buff_size;

	buff_size = 1000;
	if (b == 0)
		from_buff(dst, &bs[0][0], f);
	else
	{
		from_buff(dst, buff_sw(bs, b), buff_size);
		from_buff(dst, b, f);
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*t_dst;
	const char	*t_src;
	char		b[2][1000];
	size_t		f;
	char		*p;

	t_dst = dst;
	t_src = src;
	if (((t_dst != 0) || (t_src != 0)))
	{
		f = to_buff(&b[0][0], &t_src, 1000, ((const char *)src - t_src + len));
		p = 0;
		while ((((const char *)src - t_src + len) != 0) && (f == 1000))
		{
			p = buff_sw(b, p);
			f = to_buff(p, &t_src, 1000, ((const char *)src - t_src + len));
			if ((((const char *)src - t_src + len) != 0) && (f == 1000))
				from_buff(&t_dst, buff_sw(b, p), 1000);
		}
		final_step(p, b, f, &t_dst);
	}
	return (dst);
}
