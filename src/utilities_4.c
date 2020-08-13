/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:59:44 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 16:29:19 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_syntax(char *input)
{
	ft_printf("minishell: syntax error\n");
	set_status(2);
	free(input);
}

void	decode_command_chevrons(t_cmd *cmd)
{
	int i;
	int j;

	i = -1;
	while (cmd->args[++i])
	{
		j = -1;
		while (cmd->args[i][++j])
		{
			if (cmd->args[i][j] == 7)
				cmd->args[i][j] = '>';
			if (cmd->args[i][j] == 8)
				cmd->args[i][j] = '<';
		}
	}
}