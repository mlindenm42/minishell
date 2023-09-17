/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:10:20 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/18 00:22:15 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h> // exit(); EXIT_FAILURE;
#include <unistd.h> //NULL; write();

// void	free_all(void)
// {
// 	int	i;

// 	i = 0;
// 	while (i < get_d()->nb_of_ps && i < get_d()->nb_of_ps)
// 		pthread_join(get_d()->ps[i++]->thread, NULL);
// 	i = 0;
// 	while (i < get_d()->nb_of_ps)
// 		pthread_mutex_destroy(get_d()->forks[i++]->m_fork);
// 	pthread_mutex_destroy(&get_d()->m_dead);
// 	pthread_mutex_destroy(&get_d()->m_last_meal);
// 	pthread_mutex_destroy(&get_d()->m_finished);
// 	pthread_mutex_destroy(&get_d()->m_print);
// 	free_ps();
// 	free_forks();
// }

// don't forget to free the input

void	error(char *reason)
{
	// free_all();
	write(2, "Error\n", 6);
	write(2, reason, ft_strlen(reason));
	exit(EXIT_FAILURE);
}
