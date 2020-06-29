/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:59:51 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/29 14:59:52 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints command, args, input, and outputs of the given command.
** @param	cmd	the command to be printed.
*/

void	print_cmd(t_cmd cmd)
{
	int	i;

	i = 0;
	ft_printf("command: '%s'\nargs: ", cmd.cmd);
	while (cmd.args[i] != NULL)
	{
		ft_printf("%d: '%s' ", i, cmd.args[i]);
		i++;
	}
	ft_printf("argc: %d\n", cmd.argc);
	ft_printf("in: %d\n", cmd.in);
	i = 0;
	while (cmd.out[i] != -1)
		ft_printf("out: %d\n", cmd.out[i++]);
}
