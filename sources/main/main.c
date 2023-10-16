/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/16 22:27:12 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// dprintf(2, "p %p\n", str);
// dprintf(2, "t %s\n", str);
//printf("s %s\n", start);

t_data	*get_data(void)
{
	static t_data	all_t_data;

	return (&all_t_data);
}

void	init_gc(t_errdata *err)
{
	err->gc.dump = malloc(sizeof(t_dump));
	if (!err->gc.dump)
		printf("kekw!");
	err->gc.dump->garbage_pile = NULL;
	err->gc.dump->next = NULL;
	err->gc.dump_status = 1;
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
	burn_it_down(&err.gc, err.gc.dump);
	return (0);
}

// leaks
// expander
// echo "$PATH"sf <- auch expander
// pipes
// cd
