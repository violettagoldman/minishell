/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:39:51 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 14:58:21 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse inputs and outputs, and remove them from the args.
** @param	cmd	the command to parse
*/

void	parse_outputs(t_cmd *cmd)
{
	int	i;
	int mode;

	i = 0;
	while (i < cmd->argc)
	{
		if ((mode = get_mode(cmd->args[i])) > 0)
		{
			if (mode == 3)
				handle_input(cmd, cmd->args[i + 1]);
			else
				handle_output(mode, cmd, cmd->args[i + 1]);
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			free(cmd->args[i + 1]);
			cmd->args[i + 1] = NULL;
			i++;
		}
		i++;
	}
	remove_null_args(cmd);
}

/*
** Set argc for a given command
** @param	cmd	the command to check
*/

void	set_argc(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->args[i])
		i++;
	cmd->argc = i;
}

void	exit_message(char *arg)
{
	ft_printf("minishell: exit: %s: numeric argument required\n", arg);
	quit(1, 255);
}

void	set_escape(char *cmd, int i, char c, int *flag)
{
	if (cmd[i] == '\\' && cmd[i - 1] == '\\')
		cmd[i] = 3;
	else
	{
		cmd[i - 1] = 3;
		cmd[i] = c;
	}
	*flag = 1;
}
