/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:59:44 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 16:29:19 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_syntax(char *input)
{
	ft_printf("minishell: syntax error\n");
	set_status(2);
	free(input);
}

void	decode_command_chevrons(t_cmd *cmd)
{
	int i;
	int j;

	i = -1;
	while (cmd->args[++i])
	{
		j = -1;
		while (cmd->args[i][++j])
		{
			if (cmd->args[i][j] == 7)
				cmd->args[i][j] = '>';
			if (cmd->args[i][j] == 8)
				cmd->args[i][j] = '<';
		}
	}
}

int		check_two_following_chars(char *s, int i, char last_char)
{
	if ((s[i] == '|' || s[i] == ';') && (last_char == '|' ||
		last_char == ';'))
		return (0);
	if ((last_char == '>' && s[i] == '<') || (last_char == '<'
		&& s[i] == '>'))
		return (0);
	if (i > 2 && s[i - 2] == '>' && (s[i - 1] == '>' || s[i - 1] == ' ')
	&& s[i] == '>')
		return (0);
	if (i > 2 && s[i - 2] == '<' && (s[i - 1] == '<' || s[i - 1] == ' ')
	&& s[i] == '<')
		return (0);
	return (1);
}

/*
** Remove NULL args from a command.
** @param	cmd	the command to parse.
*/

void	remove_null_args(t_cmd *cmd)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < cmd->argc)
		j += (cmd->args[i++] != NULL);
	args = ft_calloc(j + 1, sizeof(char*));
	j = 0;
	i = 0;
	while (i < cmd->argc)
	{
		if (cmd->args[i])
			args[j++] = cmd->args[i];
		i++;
	}
	free(cmd->args);
	cmd->args = args;
}
