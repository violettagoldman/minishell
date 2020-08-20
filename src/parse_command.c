/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:58:47 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/18 22:10:57 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

/*
** Replaces backslash + an escapable character by a fake character.
*/

int		escape_backslashes(int i, char *cmd, int quote, int dquote)
{
	int flag;

	flag = 0;
	if (i > 0 && cmd[i - 1] == '\\' && cmd[i] == '\\' && !quote)
		set_escape(cmd, i, 3, &flag);
	else if (i > 0 && cmd[i - 1] == '\\' && cmd[i] == '$' && !quote)
		set_escape(cmd, i, 4, &flag);
	else if (i > 0 && cmd[i - 1] == '\\' && cmd[i] == ';' && !quote && !dquote)
		set_escape(cmd, i, 2, &flag);
	else if (i > 0 && cmd[i - 1] == '\\' && cmd[i] == '|' && !quote && !dquote)
		set_escape(cmd, i, 5, &flag);
	else if (i > 0 && cmd[i - 1] == '\\' && cmd[i] == ' ' && !quote && !dquote)
		set_escape(cmd, i, 6, &flag);
	else if (i > 0 && cmd[i - 1] == '\\' && cmd[i] == '>' && !quote && !dquote)
		set_escape(cmd, i, 7, &flag);
	else if (i > 0 && cmd[i - 1] == '\\' && cmd[i] == '<' && !quote && !dquote)
		set_escape(cmd, i, 8, &flag);
	else if (i > 0 && cmd[i - 1] == '\\' && !quote && !dquote)
		set_escape(cmd, i, cmd[i], &flag);
	return (flag);
}

/*
** Replace all spaces between double and single quotes by CTRL ascii character.
** @param	cmd	the command to encode
*/

void	encode_command(char *cmd)
{
	int	quote;
	int	dquote;
	int	i;

	quote = 0;
	dquote = 0;
	i = -1;
	while (cmd[++i])
	{
		if (i > 0 && cmd[i - 1] == '\\' &&
		((cmd[i] == '\'' && !dquote && !quote) || (cmd[i] == '"' && !quote)))
			cmd[i - 1] = 3;
		else if (escape_backslashes(i, cmd, quote, dquote))
			(void)i;
		else if (cmd[i] == '\'')
			handle_quote(&quote, &dquote, &cmd[i]);
		else if (cmd[i] == '"')
			handle_dquote(&quote, &dquote, &cmd[i]);
		else
			handle_letter(quote, dquote, &cmd[i]);
	}
}

/*
** Takes user input, splits it and executes each commands.
** @param	input	the raw user input
*/

void	parse_input(char *input)
{
	char	**commands;
	int		i;
	int		j;
	t_cmd	*cmds;

	encode_command(input);
	input = replace(input);
	if (!check_syntax(input))
	{
		exit_syntax(input);
		return ;
	}
	i = 0;
	commands = ft_split(input, ';');
	free(input);
	while (commands[i] != NULL)
	{
		cmds = parse_commands_pipe(commands[i++]);
		j = 0;
		while (cmds[j].cmd != NULL)
			exec_cmd(cmds[j++]);
		exec_cmd_helper();
		free(cmds);
	}
	free(commands);
}

/*
** Takes raw user input, and create piped commands array.
** @param	cmd	the user input
** @return		a commands list
*/

t_cmd	*parse_commands_pipe(char *cmd)
{
	char	**pipes;
	t_cmd	*cmds;
	int		i;
	t_cmd	last;

	i = 0;
	last.cmd = NULL;
	pipes = ft_split(cmd, '|');
	free(cmd);
	while (pipes[i] != NULL)
		i++;
	if (!(cmds = ft_calloc(sizeof(t_cmd), i + 1)))
		return (NULL);
	i = -1;
	while (pipes[++i])
	{
		if (!full_spaces(pipes[i]))
			cmds[i] = parse_command(pipes[i]);
		else
			free(pipes[i]);
	}
	free(pipes);
	cmds[i] = last;
	io(cmds);
	return (cmds);
}

/*
** Parse a single user command and splits command and args.
** @param	cmd	the command string
** @return		the command object
*/

t_cmd	parse_command(char *cmd)
{
	char	**pieces;
	int		i;
	t_cmd	res;

	i = 0;
	while (i < MAX_OUTPUTS)
		res.out[i++] = -1;
	parse_command_helper(&pieces, cmd);
	res.argc = 0;
	while (pieces[res.argc] != NULL)
		res.argc++;
	if (!(res.args = ft_calloc(i + 1, sizeof(char *))))
		return (res);
	i = -1;
	while (pieces[++i] != NULL)
		res.args[i] = pieces[i];
	free(pieces);
	i = 0;
	while (res.args[i])
		decode_command(res.args[i++]);
	init_cmd(&res);
	decode_command_chevrons(&res);
	return (res);
}
