/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:58:30 by vgoldman          #+#    #+#             */
/*   Updated: 2020/07/27 12:14:36 by vgoldman         ###   ########.fr       */
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
	char	*res;

	i = 0;
	getcwd(buffer, 1000);
	if (!ft_strcmp(buffer, "/"))
		return (ft_strjoin("/", ""));
	else
		dirs = ft_split(buffer, '/');
	while (dirs[i])
		i++;
	res = ft_strjoin(dirs[i - 1], "");
	free_splits(dirs);
	return (res);
}

/*
** Exits minishell.
*/

void	quit(int new_line, int status)
{
	free_splits(g_minishell.envp);
	ft_printf("exit");
	if (new_line)
		ft_printf("\n");
	exit(status);
}

/*
** Prints prompt before user input.
*/

void	print_prompt(void)
{
	char	*dir;
	int		fd;

	dir = current_directory();
	if ((fd = open(".git/HEAD", O_RDONLY)) > 0)
		print_prompt_git(dir, fd);
	else
	{
		ft_printf(BOLD);
		if (g_minishell.status == 0)
			ft_printf(GREEN"➜ "CYAN" %s "RESET, dir);
		else
			ft_printf(RED"➜ "CYAN" %s "RESET, dir);
	}
	close(fd);
	free(dir);
}

/*
** Reads user input. Block CTRL-D after user typed something but before he
** presses Enter.
** @param	buffer	the buffer to read the user input in
*/

void	read_command(char **buffer)
{
	int		i;
	char	b[1];

	i = get_next_line(1, buffer);
	if (!i && !ft_strlen(*buffer))
	{
		free(*buffer);
		quit(1, 0);
	}
	while (!i)
		i = read(1, b, 1);
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
