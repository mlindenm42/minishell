/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:04:43 by mrubina           #+#    #+#             */
/*   Updated: 2023/10/13 14:32:20 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//writes buffer to file
void	wrtofile(int end, int filefd, char *cur, char *buf)
{
	if (*cur == '\n')
	{
		if (!end)
		{
			write(filefd, buf, cur - buf + 1);
			write(1, "> ", 3);
		}
	}
	else
		write(filefd, buf, cur - buf);
}

//reads from stdin untill either the buffer is full or till newline
//returns the pointer to the last filled character of the buffer
char	*readbuf(char *buf, int size)
{
	char	*cur;

	cur = buf;
	ft_bzero(buf, size + 1);
	while (cur <= (buf + size - 1) && *cur != '\n')
	{
		read(0, cur, 1);
		if (*cur != '\n')
			cur = cur + 1;
	}
	return (cur);
}
