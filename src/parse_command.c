#include "minishell.h"

/*
** Takes user input and exec command.
*/
void	parse_input(char *input)
{
	char	**commands;
	int		i;
	int		j;
	t_cmd	*cmds;

	i = 0;
	commands = ft_split(input, ';');
	while (commands[i] != NULL)
	{
		cmds = parse_commands_pipe(commands[i++]);
		j = 0;
		while (cmds[j].cmd != NULL)
			exec_cmd(cmds[j++]);
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
	pieces = ft_split(cmd, ' ');
	free(cmd);
	res.cmd = pieces[0];
	while (pieces[i] != NULL)
		i++;
	if (!(res.args = ft_calloc(i + 1, sizeof(char *))))
	{
		// HANDLE MALLOC ERROR
		return (res);
	}
	i = 0;
	while (pieces[i] != NULL)
	{
		res.args[i] = pieces[i];
		i++;
	}
	res.args[i] = NULL;
	res.envp = NULL;
	return (res);
}