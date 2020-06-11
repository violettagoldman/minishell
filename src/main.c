#include "minishell.h"
#include <string.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_cmd cmd;
	if (!(cmd.args = (char **)malloc(sizeof(t_cmd *) * 3)))
		return (0);
	cmd.cmd = strdup("/bin/ls");
	cmd.args[0] = strdup("ls");
	cmd.args[1] = strdup("-la");
	cmd.args[2] = NULL;
	cmd.envp = strdup("PATH=/bin/");

	ft_printf("\e[1;1H\e[2J");
	prompt(cmd);
	return (0);
}
