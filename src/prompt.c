#include "minishell.h"
#include "get_next_line.h"

void	print_prompt(void)
{
	ft_printf(BOLD"$ "RESET);
}

void	read_command(char **buffer)
{
	get_next_line(0, buffer);
}

void	prompt(void)
{
	char	*cmd;

	while (1)
	{
		print_prompt();
		read_command(&cmd);
		if (!(ft_strcmp(cmd, "exit")))
			exit(0);
		parse_input(cmd);
		free(cmd);
	}
}
