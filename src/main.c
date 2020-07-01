/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:58:56 by vgoldman          #+#    #+#             */
/*   Updated: 2020/07/01 13:38:51 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

/*
**	Entry point of minishell.
*/

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_minishell.envp = copy_envp(envp);
	set_status(0);
	ft_printf("\e[1;1H\e[2J");
	prompt();
	return (0);
}
