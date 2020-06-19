#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "signal.h"
# include "libftprintf.h"
# include "get_next_line.h"
# define BOLD "\e[1m"
# define CYAN "\e[36m"
# define RESET "\e[0m"

typedef struct	s_cmd
{
	char	**args;
	char	*cmd;
	int		*in;
	int		*out;
	int		argc;
}				t_cmd;

typedef struct	s_minishell
{
	pid_t	pid;
	char	**envp;
}				t_minishell;

/* minishell */
void	prompt(void);
int		exec_cmd(t_cmd cmd);
void	parse_input(char *cmd);
t_cmd	parse_command(char *cmd);
void	print_cmd(t_cmd cmd);
t_cmd	*parse_commands_pipe(char *cmd);
void	print_prompt(void);

/* signals */
void	handle_signals(void);

/* env */
char	*get_env(char *key);
char	*get_path(char *cmd);

/* built-ins */
int		builtin(t_cmd cmd);
void	ft_echo(t_cmd cmd);
void	ft_cd(t_cmd cmd);
void	ft_export(void);
void	ft_unset(void);
void	ft_env(t_cmd cmd);
void	ft_pwd(t_cmd cmd);
void	quit(void);

/* libft */
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);

#endif
