/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 20:23:46 by vgoldman          #+#    #+#             */
/*   Updated: 2020/07/29 10:28:36 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Join a string array to a single string.
** @param	strs	the string array
*/

char	*join_splits(char **strs)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	while (strs[++i])
	{
		k = -1;
		while (strs[i][++k])
			j++;
	}
	if (!(result = (char *)ft_calloc(sizeof(char), j + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (strs[++i])
	{
		k = -1;
		while (strs[i][++k])
			result[j++] = strs[i][k];
	}
	return (result);
}

/*
** Remove '' and "" from string.
** @param	str	the string to edit.
*/

char	*remove_quotes(char *str)
{
	char	**splits;
	char	*result;

	splits = ft_split(str, 3);
	free(str);
	result = join_splits(splits);
	free_splits(splits);
	return (result);
}

/*
** Free a file name and paths.
** @param	file_name	the file name to free.
** @param	paths		the paths to free.
*/

void	free_file_name_and_paths(char *file_name, char **paths)
{
	free(file_name);
	free_splits(paths);
}

/*
** Helper funciton to parse_command to initialise pieces array.
** @param	pieces	parts of a command
** @param	cmd		the user input(command)
*/

void	parse_command_helper(char ***pieces, char *cmd)
{
	int j;

	j = -1;
	*pieces = ft_split(cmd, ' ');
	free(cmd);
	while ((*pieces)[++j])
		(*pieces)[j] = remove_quotes((*pieces)[j]);
}
