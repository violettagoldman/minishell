#include "minishell.h"

void	io(t_cmd *cmds)
{
	int	total;
	int	i;
	int	j;
	int	fd[2];

	total = 0;
	i = 0;
	while (cmds[total].cmd)
		total++;
	while (i < total)
	{
		j = 0;
		while (j < MAX_OUTPUTS)
			cmds[i].out[j++] = -1;
		if (!i)
			cmds[i].in = 0;
		else
		{
			pipe(fd);
			add_output(cmds[i - 1].out, fd[1]);
			cmds[i].in = fd[0];
		}
		if (i == total - 1)
		{
			add_output(cmds[i].out, 1);
		}
		add_output(cmds[i].out, -1);
		++i;
	}
}

void	add_output(int *fds, int fd)
{
	int i;

	i = 0;
	while (fds[i] != -1)
		i++;
	fds[i] = fd;
}

void	redirect(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.in != 0)
	{
		dup2(cmd.in, 0);
	}
	while (cmd.out[i] != -1)
	{
		if (cmd.out[i] != 1)
		{
			dup2(cmd.out[i], 1);
		}
		i++;
	}
}

void close_fd(t_cmd cmd)
{
	int	i;

	i = 0;
	if (cmd.in != 0)
		close(cmd.in);
	while (cmd.out[i] != -1)
	{
		if (cmd.out[i] != 1)
			close(cmd.out[i]);
		i++;
	}
}
