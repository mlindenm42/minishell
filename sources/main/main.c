/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/09/28 19:57:24 by mrubina          ###   ########.fr       */
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

void errinit(t_errdata *err, char *envp[])
{

	err->stat = 0;
	err->stop = CNT;
	err->statstr = NULL;
	while (*envp != NULL)
		envp++;
	err->envmem_end = *(envp - 1);
	while (*err->envmem_end != '\0')
		err->envmem_end++;
	//printf("%p\n", err->envmem_end);
	//pointer to "end of env"
}

int	main(int argc, char *argv[], char *envp[])
{
	t_errdata	err;

	errinit(&err, envp);
	set_loc_env(envp);
	//printenv(envp);
	//exit(0);
	terminal(envp, &err);
	return (0);
}
