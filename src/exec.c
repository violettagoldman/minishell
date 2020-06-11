#include "minishell.h"

#include <stdio.h>

int		exec_cmd(t_cmd cmd)
{
	pid_t	pid;
	int		exec_res;

	pid = fork();
	if (!pid && (exec_res = execve(cmd.cmd, cmd.args, &cmd.envp) < 0))
			ft_printf("Exec error %d\n", exec_res);
	else if (pid < 0)
		ft_printf("Fork error\n");
	else
		wait(&pid);
	return (1);
}
