#include "minishell.h"
#include <string.h>

t_minishell g_minishell;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_minishell.envp = envp;
	set_status(0);
	ft_printf("\e[1;1H\e[2J");
	prompt();
	return (0);
}
