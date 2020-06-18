#include "minishell.h"

extern t_minishell g_minishell;

void	ft_unset(void)
{
	ft_printf("unset");
}

void	ft_env(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.argc == 1)
		while (g_minishell.envp[i])
			ft_printf("%s\n", g_minishell.envp[i++]);
	else
		ft_printf("env: %s: No such file or directory\n", cmd.args[1]);
}
