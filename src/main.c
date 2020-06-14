#include "minishell.h"
#include <string.h>

t_minishell g_minishell;

int main(void)
{
	ft_printf("\e[1;1H\e[2J");
	prompt();
	return (0);
}
