/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:59:33 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/29 16:09:55 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

/*
** Sets the last command exit status variable in minishell global variable and
** the environment variable.
** @param	n	last command exit status
*/

void	set_status(int n)
{
	char	*nb;
	char	*res;

	nb = ft_itoa(n);
	g_minishell.status = n;
	res = ft_strjoin("?=", nb);
	add_env(res);
	free(nb);
}

/*
** Takes a command, creates a subprocess, creates i/o redirections, executes the
** command, closes redirections and subprocess.
** @param	cmd	the executed command
*/

void	exec_cmd(t_cmd cmd)
{
	pid_t	pid;
	int		exec_res;

	pid = fork();
	if (!pid)
		redirect(cmd);
	if (!pid && (exec_res = execve(cmd.cmd_abs,
					cmd.args, g_minishell.envp) < 0))
	{
		ft_printf("minishell: %s: command not found\n", cmd.cmd);
		exit(127);
	}
	else if (pid < 0)
	{
		ft_printf("minishell: fork error\n");
		exit(127);
	}
	else
	{
		g_minishell.pid = pid;
		wait(&pid);
		set_status(WEXITSTATUS(pid));
		g_minishell.pid = 0;
	}
	close_fd(cmd);
	free_cmd(cmd);
}

/*
** Frees given command object.
** @param	cmd	the command object to free.
*/

void	free_cmd(t_cmd cmd)
{
	int i;

	i = 0;
	while (cmd.args[i])
		free(cmd.args[i++]);
	free(cmd.args);
	free(cmd.cmd_abs);
}
