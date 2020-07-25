/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:59:58 by vgoldman          #+#    #+#             */
/*   Updated: 2020/07/25 17:32:16 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Builtin that prints given args.
** @param	cmd	the command executed by the user.
*/

void	ft_echo(t_cmd cmd)
{
	int		i;
	int		arg;

	i = 1;
	arg = 0;
	if (cmd.argc > 1)
	{
		if (!ft_strcmp(cmd.args[1], "-n"))
			arg = 1;
		i += arg;
		while (cmd.args[i])
		{
			ft_printf(cmd.args[i++]);
			if (i < cmd.argc)
				ft_printf(" ");
		}
		if (!arg)
			ft_printf("\n");
	}
	else
		ft_printf("\n");
}

/*
** Builtin that changes current working directory to given path.
** @param	cmd	the command executed by the user.
*/

void	ft_cd(t_cmd cmd)
{
	char	*home;

	if (cmd.argc == 1)
	{
		home = get_env("HOME");
		chdir(home);
		free(home);
	}
	else if (cmd.argc > 2)
		ft_printf("cd: too many arguments\n");
	else if (chdir(cmd.args[1]) < 0)
		ft_printf("cd: no such file or directory: %s\n", cmd.args[1]);
}

/*
** Builtin that prints the current working directory.
** @param	cmd	the command executed by the user.
*/

void	ft_pwd(void)
{
	char	buffer[1000];

	ft_printf("%s\n", getcwd(buffer, 1000));
}

/*
** Builtin that adds variables in environment variables.
** @param	cmd	the command executed by the user.
*/

void	ft_export(t_cmd cmd)
{
	int i;
	int sign;

	i = 1;
	if (cmd.argc == 1)
		ft_env(cmd);
	else
		while (i < cmd.argc)
		{
			if ((sign = equality_sign_check(cmd.args[i])) == 1)
				add_env(cmd.args[i]);
			else if (sign == -1)
				ft_printf("minishell: export: `%s': not a valid identifier\n",
						cmd.args[i]);
			i++;
		}
}

/*
** Takes a command containing a builtin and executes the associated function on.
** child process.
** @param	cmd	the command executed by the user.
*/

int		builtin(t_cmd cmd)
{
	if (!ft_strcmp(cmd.cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd.cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd.cmd, "env"))
		ft_env(cmd);
	else
		return (0);
	exit(0);
	return (1);
}
