/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:14:35 by mlindenm          #+#    #+#             */
/*   Updated: 2023/10/01 20:42:29 by mrubina          ###   ########.fr       */
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

//err->envmem_end pointer to the end of the last used character of the
//allocated memory
//we use memory after it for created variables
void errinit(t_errdata *err, char *envp[])
{

	err->stat = 0;
	err->stop = CNT;
	err->statstr = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_errdata	err;

	//replace_var("var1", "new", envp, SET);
	//replace_var("var1", NULL, envp, UNSET);
	//replace_var("OLDPWD", NULL, envp, SET);
	//printenv(envp);
	//exit(0);
	errinit(&err, envp);
	set_loc_env(envp);
	//printf("clt %s\n", "ert");
	//replace_var("COLORTERM", "ryryerye", envp, SET);
	//replace_var("LOGNAME", "iiuiuyi", envp, SET);
	//printenv(envp);
	//replace_var("SHELL", "uyivadw", envp, SET);
	//replace_var("var2", NULL, envp, UNSET);
	//printenv(envp);
	//exit(0);
	terminal(envp, &err);
	return (0);
}
