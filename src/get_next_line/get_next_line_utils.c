/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:31:17 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/07 21:55:40 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strappend(char *str, char *add, int size)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!add)
		return (str);
	while (str[i])
		i++;
	if (!(res = (char *)malloc(sizeof(char) * (size + i + 1))))
		return (NULL);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	while (j < size)
	{
		res[i + j] = add[j];
		j++;
	}
	free(str);
	res[i + j] = '\0';
	return (res);
}

char	*get_first_line(char *buffer)
{
	int		i;
	char	*res;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		res[i] = buffer[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int		breaks_checker(char *buffer)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			res++;
		i++;
	}
	return (res);
}

char	*get_rest_buffer(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i] && str[i++])
		j++;
	i -= j;
	if (!(res = (char *)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}
