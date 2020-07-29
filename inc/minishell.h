/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <tmarx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:22:26 by tmarx             #+#    #+#             */
/*   Updated: 2020/07/29 10:22:09 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "signal.h"
# include "libftprintf.h"
# include "get_next_line.h"
# define BOLD "\e[1m"
# define CYAN "\e[36m"
# define GREEN "\e[92m"
# define RED "\e[91m"
# define BLUE "\e[94m"
# define RESET "\e[0m"
# define MAX_OUTPUTS 4096

typedef struct	s_cmd
{
	char	**args;
	char	*cmd;
	char	*cmd_abs;
	int		argc;
	int		out[MAX_OUTPUTS];
	int		in;
}				t_cmd;

typedef struct	s_minishell
{
	pid_t	pid;
	char	**envp;
	int		status;
}				t_minishell;

/*
** minishell
*/

void			prompt(void);
int				exec_cmd(t_cmd cmd);
void			parse_input(char *cmd);
t_cmd			parse_command(char *cmd);
void			print_cmd(t_cmd cmd);
t_cmd			*parse_commands_pipe(char *cmd);
void			print_prompt(void);
void			print_prompt_git(char *dir, int fd);
void			set_status(int n);
void			encode_command(char *cmd);
void			handle_quote(int *quote, int *dquote, char *c);
void			handle_dquote(int *quote, int *dquote, char *c);
void			handle_letter(int quote, int dquote, char *c);
void			decode_command(char *str);
void			io(t_cmd *cmds);
void			add_output(int *fds, int fd);
void			redirect(t_cmd cmd);
void			close_fd(t_cmd cmd);
void			parse_outputs(t_cmd *cmd);
void			free_cmd(t_cmd cmd);
void			init_cmd(t_cmd *cmd);
int				set_mode(int *mode, char *arg);
void			handle_output(int mode, t_cmd *cmd, char *arg);
void			handle_input(t_cmd *cmd, char *arg);
void			exec_on_child(t_cmd cmd);
void			free_on_fail(t_cmd *cmds, int *j);
int				full_spaces(char *str);
char			*remove_quotes(char *str);
void			parse_command_helper(char ***pieces, char *cmd);

/*
** Signals
*/

void			handle_signals(void);

/*
** Env
*/

char			*get_env(char *var);
char			*get_path(char *cmd);
void			add_env(char *var);
void			remove_env(char *var);
int				equality_sign_check(char *var);
char			*replace(char *str);
char			**copy_envp(char **envp);
void			create_filename(char *path, char *cmd, char *file_name[2]);
void			free_file_name_and_paths(char *file_name, char **paths);

/*
** Built-ins
*/

int				builtin(t_cmd cmd);
int				builtin_parent(t_cmd cmd);
void			ft_echo(t_cmd cmd);
void			ft_cd(t_cmd cmd);
void			ft_export(t_cmd cmd);
void			ft_unset(t_cmd cmd);
void			ft_env(t_cmd cmd);
void			ft_pwd(void);
void			quit(int new_line, int status);

/*
** Libft
*/

int				ft_strcmp(char *s1, char *s2);
char			**ft_split(char const *s, char c);
void			free_splits(char **splits);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcat(char *dest, char *src);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, int start, int len);
char			*ft_itoa(int n);

#endif
