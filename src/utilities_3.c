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
** Takes a single command object, and parses command outputs.
** @param	cmd	the command to parse
*/

void	parse_outputs(t_cmd *cmd)
{
	int	mode;
	int	i;

	i = -1;
	mode = 0;
	while (++i < cmd->argc)
	{
		if (set_mode(&mode, cmd->args[i]))
			(void)mode;
		else if (mode == 1 || mode == 2)
			handle_output(mode, cmd, cmd->args[i]);
		else if (mode == 3)
			handle_input(cmd, cmd->args[i]);
		else if (cmd->args[i] == cmd->cmd)
			mode = 0;
		if (mode > 0)
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
		}
	}
	i = 0;
	while (cmd->args[i])
		i++;
	cmd->argc = i;
}

/*
** Parse inputs and outputs before the command, and remove them.
** @param	cmd	the command to parse
*/

void	parse_outputs_before(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i] && get_mode(cmd->args[i]))
	{
		if (get_mode(cmd->args[i]) == 3)
			handle_input(cmd, cmd->args[i + 1]);
		else
			handle_output(get_mode(cmd->args[i]), cmd, cmd->args[i + 1]);
		free(cmd->args[i]);
		free(cmd->args[i + 1]);
		i += 2;
	}
	cmd->args = cmd->args + i;
	cmd->offset = i;
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
