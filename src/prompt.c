#include "minishell.h"

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

void	quit(void)
{
	exit(0);
}

void	print_prompt(void)
{
	ft_printf(BOLD GREEN"➜ "CYAN" %s "RESET, current_directory());
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
		parse_input(cmd);
	}
}
