/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:58:30 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/29 14:58:31 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

/*
** Returns current working directory name, '/' if root
** @return	the current working directory name
*/

char	*current_directory(void)
{
	char	buffer[1000];
	char	**dirs;
	int		i;

	i = 0;
	getcwd(buffer, 1000);
	if (!ft_strcmp(buffer, "/"))
		return ("/");
	else
		dirs = ft_split(buffer, '/');
	while (dirs[i++]);
	return (dirs[i - 2]);
}

/*
** Exits minishell.
*/

void	quit(void)
{
	exit(0);
}

/*
** Prints prompt before user input.
*/

void	print_prompt(void)
{
	if (g_minishell.status == 0)
		ft_printf(BOLD GREEN"➜ "CYAN" %s "RESET, current_directory());
	else
		ft_printf(BOLD RED"➜ "CYAN" %s "RESET, current_directory());
}

/*
** Reads user input.
** @param	buffer	the buffer to read the user input in
*/

void	read_command(char **buffer)
{
	if (!get_next_line(0, buffer))
		quit();
}

/*
** The loop that: prints promt, handle user signals, gets the user input and
** execute it.
*/

void	prompt(void)
{
	char	*cmd;

	while (1)
	{
		print_prompt();
		handle_signals();
		read_command(&cmd);
		parse_input(cmd);
	}
}
