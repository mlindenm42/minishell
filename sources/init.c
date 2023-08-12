/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindenm <mlindenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:35:33 by mlindenm          #+#    #+#             */
/*   Updated: 2023/08/12 23:38:18 by mlindenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_prompt(void)
{
	if (getenv("USER") != NULL)
	{
		get_data()->prompt = getenv("USER");
		ft_strlcat(get_data()->prompt, " % ",
			ft_strlen(get_data()->prompt) + 4);
	}
	else
		get_data()->prompt = "USER % ";
}
