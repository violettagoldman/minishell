#include "minishell.h"

void	handle_quote(int *quote, int *dquote, char *c)
{
	if (!*quote && !*dquote)
	{
		*quote = 1;
		*c = ' ';
	}
	else if (*quote && !*dquote)
	{
		*quote = 0;
		*c = ' ';
	}
}

void	handle_dquote(int *quote, int *dquote, char *c)
{
	if (!*quote && !*dquote)
	{
		*c = ' ';
		*dquote = 1;
	}
	else if (!*quote && *dquote)
	{
		*c = ' ';
		*dquote = 0;
	}
}

void	handle_letter(int quote, int dquote, char *c)
{
	if ((quote || dquote) && *c == ' ')
		*c = 1;
}

void	decode_command(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 1)
			str[i] = ' ';
	}
}
