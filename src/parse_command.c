#include "minishell.h"

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
** Takes user input and exec command.
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
	while (commands[i] != NULL)
	{
		cmds = parse_commands_pipe(commands[i++]);
		j = 0;
		while (cmds[j].cmd != NULL)
		{
			if (!builtin(cmds[j]))
				exec_cmd(cmds[j]);
			j++;
		}
	}
}

/*
** Takes a command, split it by different binaries execution
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
		// HANDLE MALLOC ERROR
		return (NULL);
	}
	i = 0;
	while (pipes[i])
	{
		cmds[i] = parse_command(pipes[i]);
		i++;
	}
	cmds[i] = last;
	io(cmds);
	return (cmds);
}

/*
** Takes a single command string and converts it to an t_cmd
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
		decode_command(res.args[i]);
		i++;
	}
	res.args[i] = NULL;
	parse_outputs(&res);
	return (res);
}

void	parse_outputs(t_cmd *cmd)
{
	int	mode;
	int	i;
	int	fd;

	i = 0;
	mode = 0;
	while (i < cmd->argc)
	{
		if (!ft_strcmp(cmd->args[i], ">"))
			mode = 1;
		else if (!ft_strcmp(cmd->args[i], ">>"))
			mode = 2;
		else if (mode == 1)
		{
			if ((fd = open(cmd->args[i], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
				ft_printf("minishell: cannot create %s", cmd->args[i]);
			else
				add_output(cmd->out, fd);
		}
		else if (mode == 2)
		{
			if ((fd = open(cmd->args[i], O_WRONLY | O_CREAT | O_APPEND,
							0666)) < 0)
				ft_printf("minishell: cannot create %s", cmd->args[i]);
			else
			{
				add_output(cmd->out, open(cmd->args[i],
							O_WRONLY | O_CREAT | O_APPEND));
			}
		}
		if (mode > 0)
			cmd->args[i] = NULL;
		i++;
	}
}
