/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:59:33 by vgoldman          #+#    #+#             */
/*   Updated: 2020/07/29 13:17:13 by vgoldman         ###   ########.fr       */
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
	free(res);
	free(nb);
}

/*
** Takes a command, creates a subprocess, creates i/o redirections, executes the
** command, closes redirections and subprocess.
** @param	cmd	the executed command
*/

int		exec_cmd(t_cmd cmd)
{
	pid_t	pid;

	if (builtin_parent(cmd))
	{
		free_cmd(cmd);
		return (1);
	}
	pid = fork();
	if (!pid)
		exec_on_child(cmd);
	else if (pid < 0)
	{
		ft_printf("minishell: fork error\n");
		exit(127);
	}
	else
		exec_cmd_helper(pid);
	close_fd(cmd);
	free_cmd(cmd);
	return (g_minishell.status == 0);
}

void	exec_cmd_helper(pid_t pid)
{
	g_minishell.pid = pid;
	wait(&pid);
	if (pid == 2)
		set_status(130);
	else
		set_status(WEXITSTATUS(pid));
	g_minishell.pid = 0;
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

/*
** Takes a command and execute it in child.
** @param cmd	the command to execute
*/

void	exec_on_child(t_cmd cmd)
{
	int exec_res;

	redirect(cmd);
	if (!builtin(cmd))
	{
		if (cmd.in < 0)
			exit(1);
		cmd.cmd_abs = get_path(cmd.cmd);
		if (!cmd.cmd_abs)
			exec_res = -1;
		else
			exec_res = execve(cmd.cmd_abs, cmd.args, g_minishell.envp);
		if (exec_res < 0)
		{
			write(2, "minishell: ", 11);
			write(2, cmd.cmd, ft_strlen(cmd.cmd));
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
}
