/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <tmarx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:21:31 by tmarx             #+#    #+#             */
/*   Updated: 2020/06/29 14:00:12 by tmarx            ###   ########.fr       */
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
