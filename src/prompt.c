#include "minishell.h"

void	print_prompt(void)
{
	ft_printf(BOLD"$ "RESET);
}

void	read_command(char **buffer)
{
	get_next_line(0, buffer);
}

void	prompt(t_cmd line)
{
	char	*cmd;

	while (1)
	{
		print_prompt();
		read_command(&cmd);
		exec_cmd(line);
		if (!(ft_strcmp(cmd, "exit")))
			exit(0);
		free(cmd);
	}
}
