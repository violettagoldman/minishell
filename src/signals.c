/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:57:33 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/10 19:25:38 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

/*
** Handle the signal thrown when the user hits CTRL+C. Kill the current process.
** @param	signal	the signal value.
*/

void	handle_ctrl_c(int signal)
{
	ft_printf("\n");
	if (!g_minishell.pid)
	{
		set_status(130);
		print_prompt();
	}
	else
		kill(g_minishell.pid, signal);
}

/*
** Handle the signal thrown when the user hits CTRL+\. Kill the current process.
** @param	signal	the signal value.
*/

void	handle_ctrl_backslash(int signal)
{
	if (g_minishell.pid)
	{
		kill(g_minishell.pid, signal);
		set_status(131);
		ft_printf("\nQuit: %d\n", signal);
	}
}

/*
** Handle the signals, call the expected function.
*/

void	handle_signals(void)
{
	if (signal(SIGINT, &handle_ctrl_c) == SIG_ERR)
		ft_printf("Could not set SIGINT handler\n");
	if (signal(SIGQUIT, &handle_ctrl_backslash) == SIG_ERR)
		ft_printf("Could not set SIGQUIT handler\n");
}
