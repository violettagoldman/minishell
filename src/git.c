#include "minishell.h"

extern t_minishell g_minishell;

/*
** Prints prompt with git branch name.
** @param	current directory
*/

void	print_prompt_git(char *dir, int fd)
{
    char  *line;
    char  **split;
    char  *br;
    int   i;
    i = 0;
    get_next_line(fd, &line);
    split = ft_split(line, '/');
    while (split[i])
      i++;
    br = ft_strjoin(split[i - 1], "");
    ft_printf(BOLD);
    if (g_minishell.status == 0)
		ft_printf(GREEN"➜ "CYAN" %s "BLUE"git:("RED"%s"BLUE") "RESET, dir, br);
	else
		ft_printf(RED"➜ "CYAN" %s "BLUE"git:("RED"%s"BLUE") ", dir, br);
    free_splits(split);
    free(br);
    free(line);
}
