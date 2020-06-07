/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:23:48 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/03 15:10:45 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	handle_format(char **ptr, va_list args, int *count)
{
	t_format format;

	format.w_check = 0;
	format.s_check = 0;
	format.size = 0;
	format.width = 0;
	get_flags(ptr, &format);
	get_width(ptr, &format, args);
	get_size(ptr, &format, args);
	format.spec = **ptr;
	if (**ptr != '\0')
		(*ptr)++;
	send_to(args, &format, count);
}

void	send_to(va_list args, t_format *format, int *count)
{
	if (format->spec == 'c')
		ft_char((char)va_arg(args, int), format, count);
	else if (format->spec == 's')
		ft_string(va_arg(args, char*), format, count);
	else if (format->spec == '%')
	{
		if (format->size == 0 && format->s_check == 1 && format->width == 0
			&& format->w_check == 1)
			format->size = 1;
		ft_string("%", format, count);
	}
	else if (format->spec == 'c')
		ft_char('%', format, count);
	else if (format->spec == 'd' || format->spec == 'i')
		ft_int(va_arg(args, int), format, count);
	else if (format->spec == 'u')
		ft_unsigned_int(va_arg(args, int), format, count);
	else if (format->spec == 'x')
		ft_hexa(va_arg(args, int), format, count, "0123456789abcdef");
	else if (format->spec == 'X')
		ft_hexa(va_arg(args, int), format, count, "0123456789ABCDEF");
	else if (format->spec == 'p')
		ft_pointer(va_arg(args, long int), format, count);
}

void	get_flags(char **ptr, t_format *format)
{
	int i;

	i = 0;
	while (i < 6)
		format->flags[i++] = 0;
	while (ft_isflag(**ptr))
	{
		if (**ptr == '-')
			format->flags[0] = 1;
		else if (**ptr == '0')
			format->flags[1] = 1;
		else if (**ptr == '+')
			format->flags[2] = 1;
		else if (**ptr == ' ')
			format->flags[3] = 1;
		else if (**ptr == '#')
			format->flags[4] = 1;
		else if (**ptr == 39)
			format->flags[5] = 1;
		(*ptr)++;
	}
}

void	get_width(char **ptr, t_format *format, va_list args)
{
	if (**ptr == '*')
	{
		format->width = va_arg(args, int);
		(*ptr)++;
		format->w_check = 1;
	}
	else if (ft_isdigit(**ptr))
	{
		format->width = ft_atoi(ptr);
		format->w_check = 1;
	}
}

void	get_size(char **ptr, t_format *format, va_list args)
{
	if (**ptr == '.')
	{
		(*ptr)++;
		if (**ptr == '*')
		{
			format->size = va_arg(args, int);
			(*ptr)++;
		}
		else
			format->size = ft_atoi(ptr);
		format->s_check = 1;
	}
}
