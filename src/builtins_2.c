#include "minishell.h"

extern t_minishell g_minishell;

int		equality_sign_check(char *var)
{
	int i;

	i = 0;
	while (var[i])
	{
		if (i == 0 && var[i] == '=')
			return (-1);
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_cmd cmd)
{
	int i;

	i = 1;
	if (cmd.argc == 1)
		return ;
	else
		while (i < cmd.argc)
			remove_env(cmd.args[i++]);
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
