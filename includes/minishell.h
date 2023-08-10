/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:03:19 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/10 19:08:52 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_data {
	int				nb_of_ps;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				have_to_eat;
	long			start_time;
	int				death;
	int				finished;

}	t_data;

// check.c
// void	check_arg(int argc, char *argv[]);

// error.c
// void	error(char *reason);
// void	free_all(void);

// main.c

// utils.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t n);

#endif
