#include "minishell.h"

void	quit(void)
{
	exit(0);
}

void	print_prompt(void)
{
	ft_printf(BOLD"$ "RESET);
}

void	read_command(char **buffer)
{
	if (!get_next_line(0, buffer))
		quit();
}

void	prompt(void)
{
	char	*cmd;

	while (1)
	{
		print_prompt();
		handle_signals();
		read_command(&cmd);
		if (!(ft_strcmp(cmd, "exit")))
			quit();
		parse_input(cmd);
	}
}
