/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/12 23:37:14 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*get_data(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

int	main(void)
{
	init_prompt();
	terminal();
	return (0);
}
