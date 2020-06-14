#include "minishell.h"

extern t_minishell g_minishell;

void	handle_ctrl_c(int signal)
{
	kill(g_minishell.pid, signal);
}

void	handle_ctrl_backslash(int signal)
{
	kill(g_minishell.pid, signal);
	ft_printf("[quit %d]\n", g_minishell.pid);
}

void handle_signals(void)
{
	if (signal(SIGINT, &handle_ctrl_c) == SIG_ERR)
		ft_printf("Could not set SIGINT handler\n");
	if (signal(SIGQUIT, &handle_ctrl_backslash) == SIG_ERR)
		ft_printf("Could not set SIGQUIT handler\n");
}
