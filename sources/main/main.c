/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/18 00:25:41 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*get_data(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

int	main(int argc, char *argv[], char *envp[])
{
	terminal(envp);
	return (0);
}
