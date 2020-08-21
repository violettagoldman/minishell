/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:00:07 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 16:57:20 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

/*
** Check if a string is well-formated for environment variables. The variable is
** well-formated if it contains at least one '=' sign after the first character.
** 'A=42' is valid
** 'TEST' is not
** '=42' is not
** @param		var	the string to check
** @return			is the string valid
*/

int		equality_sign_check(char *var)
{
	int i;

	i = 0;
	if (!ft_strlen(var))
		return (-1);
	while (var[i])
	{
		if (i == 0 && var[i] == '=')
			return (-1);
		if (var[i] == ' ')
			return (-1);
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/*
** Builtin that removes variables from environment variables.
** @param	cmd	the command executed by the user.
*/

void	ft_unset(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.argc == 1)
		return ;
	else
		while (++i < cmd.argc)
		{
			if (equality_sign_check(cmd.args[i]) == -1)
				ft_printf("minishell: unset: `': not a valid identifier\n");
			else
				remove_env(cmd.args[i]);
		}
}

/*
** Builtin that prints all environment varibles.
** @param	cmd	the command executed by the user.
*/

void	ft_env(t_cmd cmd, int print_declare)
{
	int i;

	i = 0;
	if (cmd.argc == 1)
	{
		while (g_minishell.envp[i])
		{
			if (print_declare)
				ft_printf("declare -x ");
			ft_printf("%s\n", g_minishell.envp[i++]);
		}
	}
	else
	{
		ft_printf("env: %s: No such file or directory\n", cmd.args[1]);
		exit(127);
	}
}

/*
** Builtin that exits minishell.
** @param cmd	the command executed by the user.
*/

void	ft_exit(t_cmd cmd)
{
	int i;
	int ok;

	if (cmd.argc == 1)
		quit(1, g_minishell.status);
	else if (cmd.argc == 2)
	{
		i = -1;
		ok = 1;
		while (cmd.args[1][++i])
		{
			if ((cmd.args[1][i] > '9' || cmd.args[1][i] < '0')
				&& (cmd.args[1][i] != '-' && cmd.args[1][i] != '+'))
				ok = 0;
		}
		if (ok)
			quit(0, ft_atoi(&cmd.args[1]));
		else
			exit_message(cmd.args[1]);
	}
	else
		ft_printf("minishell: exit: too many arguments\n");
}

/*
** Takes a command containing a builtin and executes the associated function on.
** parent process.
** @param	cmd	the command executed by the user.
*/

int		builtin_parent(t_cmd cmd)
{
	if (!ft_strcmp(cmd.cmd, "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd.cmd, "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd.cmd, "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd.cmd, "exit"))
		ft_exit(cmd);
	else
		return (0);
	return (1);
}
