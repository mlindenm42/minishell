/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/20 13:56:36 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// dprintf(2, "p %p\n", str);
// dprintf(2, "t %s\n", str);

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
