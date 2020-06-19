#include "minishell.h"

extern t_minishell g_minishell;

int		exec_cmd(t_cmd cmd)
{
	pid_t		pid;
	int			exec_res;

	pid = fork();
	if (!pid && (exec_res = execve(get_path(cmd.cmd), cmd.args, g_minishell.envp) < 0))
	{
		ft_printf("Exec error %d: %s\n", exec_res, strerror(errno));
		exit(0);
	}
	else if (pid < 0)
	{
		ft_printf("Fork error\n");
		exit(0);
	}
	else
	{
		g_minishell.pid = pid;
		wait(&pid);
		g_minishell.pid = 0;
	}
	return (1);
}
