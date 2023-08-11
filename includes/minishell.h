/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:03:19 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/11 15:47:29 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_data {
	char	*prompt;
}	t_data;

// check.c
// void	check_arg(int argc, char *argv[]);

// error.c
// void	error(char *reason);
// void	free_all(void);

// main.c
t_data	*get_data(void);

// utils.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t n);

//utils_ft_split.c
char	**ft_split(char const *s, char c);

#endif
