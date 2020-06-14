#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include "signal.h"
# include "libftprintf.h"
# include "get_next_line.h"
# define BOLD "\e[1m"
# define RESET "\e[0m"

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	char	*envp;
	int		*in;
	int		*out;
}				t_cmd;

typedef struct	s_minishell
{
	pid_t	pid;
}				t_minishell;

/* minishell */
void	prompt(void);
int		exec_cmd(t_cmd cmd);
void	parse_input(char *cmd);
t_cmd	parse_command(char *cmd);
void	print_cmd(t_cmd cmd);
t_cmd	*parse_commands_pipe(char *cmd);

/* signals */
void	handle_signals(void);

/* libft */
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);

#endif
