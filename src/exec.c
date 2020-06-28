#include "minishell.h"

extern t_minishell g_minishell;

void	set_status(int n)
{
	char	*nb;
	char	*res;

	nb = ft_itoa(n);
	g_minishell.status = n;
	res = ft_strjoin("?=", nb);
	add_env(res);
	free(nb);
}

int		exec_cmd(t_cmd cmd)
{
	pid_t	pid;
	int		exec_res;

	pid = fork();
	if (!pid)
		redirect(cmd);
	if (!pid && (exec_res = execve(get_path(cmd.cmd),
					cmd.args, g_minishell.envp) < 0))
	{
		ft_printf("minishell: %s: command not found\n", cmd.cmd);
		exit(127);
	}
	else if (pid < 0)
	{
		ft_printf("minishell: fork error\n");
		exit(127);
	}
	else
	{
		g_minishell.pid = pid;
		wait(&pid);
		set_status(WEXITSTATUS(pid));
		g_minishell.pid = 0;
	}
	close_fd(cmd);
	return (1);
}
