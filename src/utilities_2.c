/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:23:51 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 13:43:17 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get the relative path of a binary.
** @param	cmd	the binary name
** @return	the relative path
*/

char	*get_relative_path(char *cmd)
{
	struct stat	buffer;

	if (!stat(cmd, &buffer))
		return (ft_strjoin(cmd, ""));
	else
		return (0);
}

/*
** Check if a string contains only one particular character
** @param	c	a character
** @return		a string to Check
*/

int		contains_only(char c, char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (1);
		i++;
	}
	return (0);
}

/*
** Check if an unser input have a valid syntax.
** @param	s	the string to check
** @return		is the string valid
*/

int		check_syntax(char *s)
{
	int		i;
	char	last_char;

	if (s[0] == ';' || s[0] == '|')
		return (0);
	i = 0;
	last_char = 0;
	while (s[i])
	{
		if ((s[i] == '|' || s[i] == ';') && (last_char == '|' ||
			last_char == ';'))
			return (0);
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\f'
			&& s[i] != '\r' && s[i] != '\v')
			last_char = s[i];
		if (i > 2 && s[i - 2] == '>' && (s[i - 1] == '>' || s[i - 1] == ' ')
		&& s[i] == '>')
			return (0);
		++i;
	}
	if (i > 1 && s[i - 1] == '|' && s[i - 2] != '\\')
		return (0);
	return (1);
}

/*
** Check if an input starts with a chevron, if yes the cmd is the last arg.
** @param	cmd	the command to process
*/

void	parse_first_chevron(t_cmd *cmd)
{
	int	i;

	if (!cmd->argc)
		return ;
	i = 0;
	while (cmd->args[i] && (!ft_strncmp(cmd->args[i], ">", 1) ||
		!ft_strcmp(cmd->args[i], "<")))
		i += 2;
	if (!cmd->args[i])
		cmd->cmd = NULL;
	else
		cmd->cmd = ft_strjoin(cmd->args[i], "");
}

/*
** Returns the file mode for a gievn string, > -> 1, >> -> 2, < -> 3
** @param	c	the string to check
** @return		the mode of the string
*/

int		get_mode(char *c)
{
	if (!ft_strcmp(c, ">"))
		return (1);
	if (!ft_strcmp(c, ">>"))
		return (2);
	if (!ft_strcmp(c, "<"))
		return (3);
	return (0);
}
