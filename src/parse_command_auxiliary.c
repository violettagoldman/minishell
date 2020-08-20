/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_auxiliary.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:04:40 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 12:22:32 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Auxiliary function for parse_command to setup the cmd struct.
** @param cmd the command to setup
*/

void	init_cmd(t_cmd *cmd)
{
	int	i;

	cmd->cmd_abs = NULL;
	cmd->in = 0;
	parse_first_chevron(cmd);
	parse_outputs(cmd);
	set_argc(cmd);
	i = -1;
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] == 3)
		{
			free(cmd->args[i]);
			cmd->args[i] = ft_strjoin("", "");
		}
	}
}

/*
** Sets the current output mode for following arguments.
** @param mode	the mode, 0=command arg, 1=output, 2=output with append, 3=input
** @param arg		the current param
*/

int		set_mode(int *mode, char *arg)
{
	if (!ft_strcmp(arg, ">"))
		*mode = 1;
	else if (!ft_strcmp(arg, ">>"))
		*mode = 2;
	else if (!ft_strcmp(arg, "<"))
		*mode = 3;
	else
		return (0);
	return (1);
}

/*
** Create a file descriptor and add it to the command.
** @param mode	1=output, 2=output with append
** @param cmd		the cmd to append file descriptor
** @param arg		the current arg
*/

void	handle_output(int mode, t_cmd *cmd, char *arg)
{
	int flags;
	int	fd;

	flags = mode == 1 ?
		O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;
	if ((fd = open(arg, flags, 0666)) < 0)
		ft_printf("minishell: cannot create %s\n", arg);
	else
		add_output(cmd->out, fd);
}

/*
** Create a file descriptor and set it as command input.
** @param mode	1=output, 2=output with append
** @param cmd		the cmd to append file descriptor
** @param arg		the current arg
*/

void	handle_input(t_cmd *cmd, char *arg)
{
	int flags;
	int	fd;

	flags = O_RDONLY;
	if ((fd = open(arg, flags)) < 0)
		ft_printf("minishell: cannot read %s\n", arg);
	cmd->in = fd;
}

/*
** If a command fails, free next ones.
** @param cmds	the array of commands
** @param j 		the index of the command that have failed
*/

void	free_on_fail(t_cmd *cmds, int *j)
{
	(*j)++;
	while (cmds[*j].cmd)
		free_cmd(cmds[(*j)++]);
}
