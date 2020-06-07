/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 23:15:38 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/07 21:55:09 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFFER_SIZE 1000

int		get_next_line(int fd, char **line);
char	*get_rest_buffer(char *str);
int		breaks_checker(char *buffer);
char	*get_first_line(char *buffer);
char	*ft_strappend(char *str, char *add, int size);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);

#endif
