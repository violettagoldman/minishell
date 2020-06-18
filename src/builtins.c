#include "minishell.h"

void	ft_echo(t_cmd cmd)
{
	int		i;
	int		arg;

	i = 1;
	arg = 0;
	if (cmd.argc > 1)
	{
		if (!ft_strcmp(cmd.args[1], "-n"))
			arg = 1;
		i += arg;
		while (cmd.args[i])
		{
			ft_printf(cmd.args[i++]);
			if (i < cmd.argc)
				ft_printf(" ");
		}
		if (!arg)
			ft_printf("\n");
	}
	else
		ft_printf("\n");
}

void	ft_cd(t_cmd cmd)
{
	(void)cmd;
	ft_printf("cd");
}

void	ft_pwd(void)
{
	ft_printf("pwd");
}

void	ft_export(void)
{
	ft_printf("export");
}

int		builtin(t_cmd cmd)
{
	if (!ft_strcmp(cmd.cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd.cmd, "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd.cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd.cmd, "export"))
		ft_export();
	else if (!ft_strcmp(cmd.cmd, "unset"))
		ft_unset();
	else if (!ft_strcmp(cmd.cmd, "env"))
		ft_env();
	else if (!ft_strcmp(cmd.cmd, "exit"))
		quit();
	else
		return (0);
	return (1);

}
