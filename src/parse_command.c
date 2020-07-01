/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:58:47 by vgoldman          #+#    #+#             */
/*   Updated: 2020/07/01 14:13:32 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cmd[i] == '\'')
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

	input = replace(input);
	encode_command(input);
	i = 0;
	commands = ft_split(input, ';');
	free(input);
	while (commands[i] != NULL)
	{
		cmds = parse_commands_pipe(commands[i++]);
		j = 0;
		while (cmds[j].cmd != NULL)
			exec_cmd(cmds[j++]);
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
	{
		return (NULL);
	}
	i = 0;
	while (pipes[i])
	{
		cmds[i] = parse_command(pipes[i]);
		i++;
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
	i = 0;
	pieces = ft_split(cmd, ' ');
	free(cmd);
	res.cmd = pieces[0];
	while (pieces[i] != NULL)
		i++;
	res.argc = i;
	if (!(res.args = ft_calloc(i + 1, sizeof(char *))))
		return (res);
	i = 0;
	while (pieces[i] != NULL)
	{
		res.args[i] = pieces[i];
		decode_command(res.args[i++]);
	}
	free(pieces);
	res.args[i] = NULL;
	res.cmd_abs = NULL;
	parse_outputs(&res);
	return (res);
}

/*
** Takes a single command object, and parses command outputs.
** @param	cmd	the command to parse
*/

void	parse_outputs(t_cmd *cmd)
{
	int	mode;
	int	i;
	int	fd;
	int	flags;

	i = -1;
	mode = 0;
	while (++i < cmd->argc)
	{
		if (!ft_strcmp(cmd->args[i], ">"))
			mode = 1;
		else if (!ft_strcmp(cmd->args[i], ">>"))
			mode = 2;
		else if (mode == 1 || mode == 2)
		{
			flags = mode == 1 ?
				O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;
			if ((fd = open(cmd->args[i], flags, 0666)) < 0)
				ft_printf("minishell: cannot create %s", cmd->args[i]);
			else
				add_output(cmd->out, fd);
		}
		if (mode > 0)
			cmd->args[i] = NULL;
	}
	i = 0;
	while (cmd->args[i])
		i++;
	cmd->argc = i;
}
