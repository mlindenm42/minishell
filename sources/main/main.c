/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/17 10:20:23 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_gc(t_errdata *err)
{
	err->gc.elem = malloc(sizeof(t_free_elem));
	if (!err->gc.elem)
		printf("kekw!");
	err->gc.elem->elem = NULL;
	err->gc.elem->next = NULL;
	err->gc.elemcounter = 1;
}

//err->envmem_end pointer to the end of the last used character of the
//allocated memory
//we use memory after it for created variables
static void	errinit(t_errdata *err, char *envp[])
{
	err->stat = 0;
	err->stop = CNT;
	err->statstr = NULL;
	err->edata = NULL;
	err->tbl = NULL;
	err->envp = envp;
	init_gc(err);
}

t_data	*get_data(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_errdata	err;
	int			test1;
	char		**test2;

	test1 = argc;
	test2 = argv;
	test1 = 0;
	test2 = NULL;
	if (test1 || test2)
		printf("STOP\n");
	errinit(&err, envp);
	set_loc_env(envp, &err);
	terminal(envp, &err);
	free_data(&err.gc, err.gc.elem);
	return (0);
}
