#include "minishell.h"

int main(void)
{
	ft_printf("\e[1;1H\e[2J");
	prompt();
	return (0);
}
