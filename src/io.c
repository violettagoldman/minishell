/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:59:27 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/29 22:00:56 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Set input and outputs file descriptors of a commands list piped in each
** other.
** @param	cmds	array of commands piped into the next one
*/

void	io(t_cmd *cmds)
{
	int	total;
	int	i;
	int	fd[2];

	total = 0;
	i = 0;
	while (cmds[total].cmd)
		total++;
	while (i < total)
	{
		if (!i)
			cmds[i].in = 0;
		else
		{
			pipe(fd);
			add_output(cmds[i - 1].out, fd[1]);
			cmds[i].in = fd[0];
		}
		if (i == total - 1)
		{
			add_output(cmds[i].out, 1);
		}
		add_output(cmds[i].out, -1);
		++i;
	}
}

/*
** Adds a file descriptor in a command outputs.
** @param	fds	array of file descriptors
** @param	fd	the file descriptor to add
*/

void	add_output(int *fds, int fd)
{
	int i;

	i = 0;
	while (fds[i] != -1)
		i++;
	fds[i] = fd;
}

/*
** Plugs STDIN and STDOUT to the pipe between two processes.
** @param	cmd	the command to execute
*/

void	redirect(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.in != 0)
		dup2(cmd.in, 0);
	while (cmd.out[i] != -1)
	{
		if (cmd.out[i] != 1)
			dup2(cmd.out[i], 1);
		i++;
	}
}

/*
** Closes all file descriptors opened when the command has been executed.
** @param	cmd	the command that has been executed
*/

void	close_fd(t_cmd cmd)
{
	int	i;

	i = 0;
	if (cmd.in != 0)
		close(cmd.in);
	while (cmd.out[i] != -1)
	{
		if (cmd.out[i] != 1)
			close(cmd.out[i]);
		i++;
	}
}
