/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:42:33 by vgoldman          #+#    #+#             */
/*   Updated: 2019/11/29 11:06:55 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	int		count;
	char	*ptr;
	va_list args;

	count = 0;
	ptr = (char *)format;
	va_start(args, format);
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			handle_format(&ptr, args, &count);
		}
		else
			ft_putnchar(*(ptr++), 1, &count);
	}
	va_end(args);
	return (count);
}
