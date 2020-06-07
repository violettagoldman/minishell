/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:20:00 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/07 22:08:57 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	error_gnl(char *s)
{
	perror(s);
	exit(-1);
}

int		get_next_line(int fd, char **line)
{
	static char		*res;
	char			buffer[BUFFER_SIZE];
	int				status;

	*line = NULL;
	status = 2;
	if (!res && !(res = ft_calloc(1, sizeof(char))))
		return (-1);
	while (!breaks_checker(res) && (status = read(fd, buffer, BUFFER_SIZE)) > 0)
		res = ft_strappend(res, buffer, status);
	if (status < 0)
		error_gnl("Error\nEmpty file");
	else if (status == 0)
	{
		*line = get_first_line(res);
		res = get_rest_buffer(res);
		free(res);
		res = NULL;
		return (0);
	}
	*line = get_first_line(res);
	res = get_rest_buffer(res);
	return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (!(ptr = (char *)malloc(count * size)))
		return (NULL);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *ptr;

	ptr = b;
	while (len-- > 0)
		*ptr++ = c;
	return (b);
}
