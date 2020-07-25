/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 20:23:46 by vgoldman          #+#    #+#             */
/*   Updated: 2020/07/25 20:43:28 by vgoldman         ###   ########.fr       */
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
