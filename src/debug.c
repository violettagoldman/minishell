#include "minishell.h"

void	print_cmd(t_cmd cmd)
{
	int	i;

	i = 0;
	ft_printf("command: '%s'\nargs: ", cmd.cmd);
	while (cmd.args[i] != NULL)
	{
		ft_printf("%d: '%s' ", i, cmd.args[i]);
		i++;
	}
	ft_printf("argc: %d\n", cmd.argc);
}
