#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include "libftprintf.h"
# define BOLD "\e[1m"
# define RESET "\e[0m"

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	int		*in;
	int		*out;
}				t_cmd;

/* minishell */
void	prompt(void);

/* libft */
int		ft_strcmp(char *s1, char *s2);

#endif
