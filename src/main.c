/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <tmarx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:21:50 by tmarx             #+#    #+#             */
/*   Updated: 2020/06/29 13:23:09 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_minishell g_minishell;

/*
**	Entry point of minishell.
*/

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_minishell.envp = envp;
	set_status(0);
	ft_printf("\e[1;1H\e[2J");
	prompt();
	return (0);
}
