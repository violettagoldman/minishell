/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 09:37:54 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/02 14:51:54 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_hexa(long int i, t_format *format, int *count, char *str)
{
	int fill_spaces;
	int fill_zero;

	fill_spaces = 0;
	fill_zero = 0;
	if (i < 0)
		i += 4294967296;
	if (format->s_check && format->size == 0 && format->flags[1])
		format->flags[1] = 0;
	ft_hh(i, format, &fill_spaces, &fill_zero);
	if (!(format->flags[0]) && !(format->flags[1]))
		ft_putnchar(' ', fill_spaces, count);
	if (!(format->flags[0]) && format->flags[1])
		ft_putnchar('0', fill_spaces, count);
	ft_putnchar('0', fill_zero, count);
	if (format->flags[4])
		ft_putnstr((str[10] == 'A' ? "0X" : "0x"), 2, count);
	if (format->size != 0 || i != 0 || !(format->s_check))
		ft_putnbr_hexa(i, count, str);
	if (format->flags[0])
		ft_putnchar(' ', fill_spaces, count);
}

void	ft_hh(long int i, t_format *format, int *fill_spaces, int *fill_zero)
{
	if ((format->size == 0 && format->s_check && i == 0)
		|| (format->s_check && format->size > 0)
			|| (format->width < len_nb_hexa(i, format) && format->size < 0))
		format->flags[1] = 0;
	if (format->width < 0)
		format->flags[0] = 1;
	if (format->flags[1] && format->width > 0)
		*fill_zero = ft_abs(format->width) - len_nb_hexa(i, format);
	else if (format->size > len_nb_hexa(i, format)
		|| (format->flags[1] && format->s_check && format->w_check))
	{
		*fill_zero = ft_abs(format->size) - len_nb_hexa(i, format) +
			(i < 0 && format->size > 0);
	}
	if (ft_abs(format->width) > len_nb_hexa(i, format) + *fill_zero)
	{
		*fill_spaces = ft_abs(format->width) - len_nb_hexa(i, format)
			- (*fill_zero < 0 ? 0 : *fill_zero);
	}
	if (format->size == 0 && format->s_check && i == 0 && format->w_check
			&& format->width != 0)
	{
		format->flags[1] = 0;
		(*fill_spaces)++;
	}
}

void	ft_pointer(long int i, t_format *format, int *count)
{
	format->flags[4] = 1;
	ft_hexa(i, format, count, "0123456789abcdef");
}
