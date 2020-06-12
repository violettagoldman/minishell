#include "minishell.h"

void	handle_ctrl_c(int signal)
{
	(void)signal;
	ft_printf("CTRL-C");
}

void	handle_ctrl_backslash(int signal)
{
	(void)signal;
	ft_printf("CTRL-'\'");
}

void handle_signals(void)
{
	if (signal(SIGINT, handle_ctrl_c) == SIG_ERR)
		ft_printf("Could not set signal handler\n");
	if (signal(SIGQUIT, handle_ctrl_backslash) == SIG_ERR)
		ft_printf("Could not set signal handler\n");
}
