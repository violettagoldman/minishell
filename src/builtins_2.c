/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <tmarx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:21:21 by tmarx             #+#    #+#             */
/*   Updated: 2020/06/29 13:55:06 by tmarx            ###   ########.fr       */
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
	while (var[i])
	{
		if (i == 0 && var[i] == '=')
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

	i = 1;
	if (cmd.argc == 1)
		return ;
	else
		while (i < cmd.argc)
			remove_env(cmd.args[i++]);
}

/*
** Builtin that prints all environment varibles.
** @param	cmd	the command executed by the user.
*/

void	ft_env(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.argc == 1)
		while (g_minishell.envp[i])
			ft_printf("%s\n", g_minishell.envp[i++]);
	else
		ft_printf("env: %s: No such file or directory\n", cmd.args[1]);
}
