/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:58:39 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 16:26:42 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sets quote and dquote in fonction of current characters.
** @param	quote		is the current character after an open quote
** @param	dquote	is the current character after an open double quote
** @param	c				the current character
*/

void	handle_quote(int *quote, int *dquote, char *c)
{
	if (!*quote && !*dquote)
	{
		*quote = 1;
		*c = 3;
	}
	else if (*quote && !*dquote)
	{
		*quote = 0;
		*c = 3;
	}
}

/*
** Sets quote and dquote in fonction of current characters.
** @param	quote		is the current character after an open quote
** @param	dquote	is the current character after an open double quote
** @param	c				the current character
*/

void	handle_dquote(int *quote, int *dquote, char *c)
{
	if (!*quote && !*dquote)
	{
		*c = 3;
		*dquote = 1;
	}
	else if (!*quote && *dquote)
	{
		*c = 3;
		*dquote = 0;
	}
}

/*
** Replaces space by CTRL character if necessary.
** @param	quote		is the current character after an open quote
** @param	dquote	is the current character after an open double quote
** @param	c				the current character
*/

void	handle_letter(int quote, int dquote, char *c)
{
	if ((quote || dquote) && *c == ' ')
		*c = 1;
	if ((quote || dquote) && *c == ';')
		*c = 2;
	if (quote && *c == '$')
		*c = 4;
	if ((quote || dquote) && *c == '|')
		*c = 5;
	if ((quote || dquote) && *c == '>')
		*c = 7;
	if ((quote || dquote) && *c == '<')
		*c = 8;
}

/*
** Replaces CTRL characters by spaces
** @param	str	the string to replace in
*/

void	decode_command(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 1)
			str[i] = ' ';
		if (str[i] == 2)
			str[i] = ';';
		if (str[i] == 4)
			str[i] = '$';
		if (str[i] == 5)
			str[i] = '|';
		if (str[i] == 6)
			str[i] = ' ';
	}
}

/*
** Check if a string contains only spaces.
** @param	str	the string to check
*/

int		full_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			return (0);
	}
	return (1);
}
